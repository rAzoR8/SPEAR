//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_MANDELBROT_H
#define SPEAR_MANDELBROT_H

#include "SPIRVProgram.h"
#include "CommonBufferSourceNames.h"

namespace Spear
{
	template <bool Assemble = true>
	class Mandelbrot : public FragmentProgram<Assemble>
	{
	public:
		Mandelbrot() : FragmentProgram<Assemble>("Mandelbrot"){};
		~Mandelbrot() {};

		//CBuffer<float3_t> FrameBufferDim = BufferSources::sFrameBufferDimension;

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
	private:
	};

} // Spear

#endif // !SPEAR_MANDELBROT_H
