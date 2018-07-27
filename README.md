# SPEAR: C++/SPIR-V Shader Runtime

## Overview

SPEAR is a integrated domain specific language translating C++17 to SPIR-V at host runtime.

```cpp
template <bool Assemble = true>
class Mandelbrot : public FragmentProgram<Assemble>
{
public:
	Mandelbrot() : FragmentProgram<Assemble>("Mandelbrot"){};
	~Mandelbrot() {};

	RenderTarget OutputColor;
	inline void operator()()
	{
		f32 i = 0.f, max = 100.f;
		complex c(Lerp(-1.f, 1.f, kFragCoord.x / 1600.f), kFragCoord.y / 900.f);
		complex z(0.f, 0.f);
		While(z.Conjugate() < 4.f && i < max)
		{
			z = z * z + c;
			++i;
		});
		f32 scale = i / max;
		OutputColor = float4(scale, scale, scale, 0.f);
	};
};
```

SPIR-V shader generated from SPEAR code above, rendered with Vulkan:
![Mandelbrot rendered from SPEAR shader](misc/fractal.png)

## Benefits

* Modern C++ features like templating & auto type deduction, Polymorphism
* Software design patterns, modularity and reusability
* Adapting cutting edge GPU features using extension
* C++ Profiling and Debugging Tools
* Quite fast for compiling many shader permutations (Makes it possible to compile during runtime for small shaders)
* Interchangeable Shading Libraries (Hot-swapping shader DLLs during rendering)
* Write meta programs / code generators
* Vulkan interoperability: create PSOs from SPIRVModules

![Debugging with Visual Studio](misc/vs_shader_dbg.png)

## Restrictions

Please don't use this for production, the codebase is largely untested and not guaranteed to work. See it as a Proof-of-Concept.

* Variable types are rather long outside the SPIRVProgram context
* Ugly macros for If, While, For etc…
* Mixing regular C++ variables and var_t<> has undesired sideeffects
* C++ variables are interpreted as constants 
* Vector components can not be extracted by reference
* Recursion is not supported (will blow up instruction recording)
* Return statements will lead to dead code (not translated)
* Missing keywords switch, continue and break
* Ternary conditional operator? can not be overloaded in C++ (Use Select function instead!)

Please read to accompanying paper [Development of a C++/SPIR-V Shader-Runtime](misc/Paper.pdf) and presentation [slides](misc/Slides.pdf) from the Khronos Meetup for more information.

## Build

The SPEAR project currently uses CMake to generate build files. In the root of this project is a `CMakeLists.txt`, which should work for generating Visual Studio solutions. There are some issues when generating Makefiles for GNU Make, but it should in theory work with a bit of fiddling. The requirements are: a `C++17` compliant compiler, a Vulkan SDK and runtime somewhere in your system, which are resolved automatically by CMake. You'll also need `boost` somewhere in your include path, or, alternatively, under `libs/boost` (just the headers, which you can get [here](https://dl.bintray.com/boostorg/release/1.67.0/source/)). The rest of the dependencies `glm`, `spirv-headers` and `spirv-tools` are fetched automatically by git submodules, and should in theory work out-of-the-box.

**Note:** this is a *very* experimental CMake-file! You might need to hack a bit to make it work on your platform, but it should at least work on a target with Visual Studio & LunarG SDK. Also, it isn't nice enough to provide `find_package` in CMake yet, you'll have to do that sort of stuff manually for now. If you have any improvements, feel free to issue a pull request!

Below is a complete summary of the steps you need to build SPEAR for Visual Studio 2017:

1. Clone this repository down to disk: `git clone https://github.com/rAzoR8/SPEAR`
2. Download `boost` (if it's not in your global include path), and put the headers under `libs/boost`
3. Fetch the rest of the dependencies with: `git submodule init && git submodule update`
4. Generate the Visual Studio solution with `cmake-gui`, modify the *build options* as you see fit.
5. Open the solution in Visual Studio, and set `SPIRVGenTest` as the target project. Build and run.

### Build options

* **SPEAR_ENABLE_PROPERTIES    = ON | OFF (default: ON):** Many convenience facilities are based on __declspec(property), and are not available on e.g. gcc. However, the library can be used without them fine.
* **SPEAR_BUILD_TESTBED        = ON | OFF (default: ON):** Also build the accompanying example project, depending on the libSPEARGen.  This gets you an executable e.g SPEARGenTest that you can (hopefully) run.
* **SPEAR_BUILD_SHADER_FACTORY = ON | OFF (default: ON):** Also build the dynamic shader library project and links it to libSPEARGen, which will be a shared library called libSPEARShaderFactory.so on Unix-es.

### Source code organization

* `SPIRVGen`: Core Spear library
* `SPIRVGenTest`: Simple testbed project
* `SPIRVShaderFactory`: Dynamic shader library example project
* `spirv-tools`: Target output folder for spirv-tool cmake
* `spirv-headers`: SPIRV headers to be used when building
* `boost`: Used for including the boost.DLL library

`SPIRVGen` library project requires Vulkan-SDK files and HLX (submodule) headers.
`SPIRVGenTest` executable project should link `SPIRVGen`.
`SPIRVShaderFactory` shared library project links `SPIRVGen` and requires boost.DLL libraries for the IPlugin DLL interface. Compile with HDYNAMIC_LINKAGE and HDLL_EXPORT defines to create a dynamic shader library.

## Usage

Please look for the example shaders located at SPIRVShaderFactory folder.

## License
```
Copyright 2018 Fabian Wahlster
Contact: f.wahlster@tum.de

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
Naming the author(s) of this software in any of the following locations: About page, README file, credits.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

## Contributing

The SPEAR project is maintained by Fabian Wahlster and hosted at https://github.com/razor8/SPEAR.

Special thanks go to:
* Mathias Kanzler
