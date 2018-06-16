# SPEAR: C++/SPIR-V Shader Runtime
# https://github.com/razor8/SPEAR/
#
# Building: create an out-of-source build directory, e.g. `build`, and go to it.
# Call `cmake ..` and provide any extra configuration settings you might need to
# make it work. All configs that can be given are shown below and in the README:
#
# SPEAR_ENABLE_PROPERTIES    = ON | OFF (default: OFF)
#     Many convenience facilities are based on __declspec(property), and are not
#     available on e.g. gcc. However, the library can be used without them fine.
#
# SPEAR_BUILD_TESTBED        = ON | OFF (default:  ON)
#     Also build the accompanying example project, depending on the libSPEARGen.
#     This gets you an executable e.g SPEARGenTest that you can (hopefully) run.
#
# SPEAR_BUILD_SHADER_FACTORY = ON | OFF (default:  ON)
#     Also build the dynamic shader library project and links it to libSPEARGen,
#     which will be a shared library called libSPEARShaderFactory.so on Unix-es.
#
# After this CMake should have generated target-specific build files in `build`.
# If the target was GNU Make you should call `make` (and probably give -j8 too),
# and if your target is a Visual Studio solution, just open it and compile this.
#
# Acknowledgements: heavily inspired by the Vulkan/CMakeLists & glfw/CMakeLists.
# Note: this script was written by Erik S. V. Jansson <caffeineviking@gmail.com>
# and is neither general or pretty, if you can, consider contributing. This file
# is released under the same license as the rest of the SPEAR project, as below:
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.  Naming the author(s) of this
# software in any of the following locations: About page, README file, credits.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.8)

project(SPEAR VERSION 1.0 LANGUAGES CXX DESCRIPTION "C++/SPIR-V Shader Runtime")
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

set(SPEAR_VERSION_MAJOR "1")
set(SPEAR_VERSION_MINOR "0")
set(SPEAR_VERSION "${SPEAR_VERSION_MAJOR}.${SPEAR_VERSION_MINOR}")

option(SPEAR_BUILD_TESTBED "Builds the SPEAR project testbed." ON)
option(SPEAR_BUILD_SHADER_FACTORY "Builds the dynamic shader loader." ON)
option(SPEAR_ENABLE_PROPERTIES "Enable optional property generation." OFF)
if (SPEAR_ENABLE_PROPERTIES) # Conditionally removes _declspec(properties)
    add_definitions(-DSPEAR_ENABLE_PROPERTIES)
endif()

find_package(Vulkan REQUIRED) # Maybe constrain this to 1.0 since we have 1.1.

if (NOT Vulkan_FOUND)
    if (WIN32)
        # Shamelessly snatched from Vulkan/CMakeLists, tries to find Vulkan's library elsewhere.
        find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS ${CMAKE_SOURCE_DIR}/libs/vulkan)
        if (Vulkan_LIBRARY)
            set(Vulkan_FOUND ON)
            MESSAGE("Using local Vulkan library.")
        endif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")
    else (WIN32)
        find_library(Vulkan_LIBRARY NAMES vulkan HINTS "$ENV{VULKAN_SDK}/lib" "${CMAKE_SOURCE_DIR}/libs/vulkan" REQUIRED)
        if (Vulkan_LIBRARY)
            set(Vulkan_FOUND ON)
            MESSAGE("Using local Vulkan library.")
        endif()
    endif()
endif()

add_subdirectory(spirv-headers) # These are also bundled with some Vulkan SDKs.
add_subdirectory(spirv-tools) # For linking the spirv-tools library with SPEAR.

add_library(libSPEARGen SHARED ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVAssembler.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVConstant.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVDecoration.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVInstruction.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVModule.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVOperation.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVType.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVVariable.cpp)
target_include_directories(libSPEARGen PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen
                                       PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hlx/include
                                               ${Vulkan_INCLUDE_DIRS}
                                               ${SPIRV-Headers_SOURCE_DIR}/include
                                               ${spirv-tools_SOURCE_DIR}/include)
set_target_properties(libSPEARGen PROPERTIES VERSION   ${PROJECT_VERSION})
set_target_properties(libSPEARGen PROPERTIES SOVERSION ${PROJECT_VERSION})
set_target_properties(libSPEARGen PROPERTIES FRAMEWORK ON)
target_link_libraries(libSPEARGen ${Vulkan_LIBRARY})

set(SPEAR_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVAssembler.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVBinaryDefines.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVBranchOperations.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVComplex.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVConstant.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVDecoration.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVExtensionAMD.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVInlineAssembler.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVInstruction.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVInterop.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVModule.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVOperation.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVOperatorImpl.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVProgram.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVQuaternion.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVType.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVVariable.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVVariableTypeDefs.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVVariableTypes.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen/SPIRVVectorComponentAccess.h)

# Below we define the headers that will be exported to the platform dep. path.
set_target_properties(libSPEARGen PROPERTIES PUBLIC_HEADER "${SPEAR_INCLUDES}")
# When installing, copy over the shared library and the header files.
install(TARGETS libSPEARGen LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (SPEAR_BUILD_SHADER_FACTORY)
    find_package(Boost 1.64 REQUIRED) # Maybe a bit too recent version, we can probably decrease this if problematic.
    add_library(libSPEARShaderFactory SHARED ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/DefaultShaderFactory.cpp)
    target_include_directories(libSPEARShaderFactory PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory
                                                     PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hlx/include
                                                             ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen
                                                             ${Vulkan_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
    target_link_libraries(libSPEARShaderFactory libSPEARGen ${Boost_LIBRARIES} ${Vulkan_LIBRARY})
    set_target_properties(libSPEARShaderFactory PROPERTIES FRAMEWORK ON VERSION ${PROJECT_VERSION})
    set_target_properties(libSPEARShaderFactory PROPERTIES SOVERSION ${PROJECT_VERSION})

    set(SPEAR_SHADER_FACTORY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/CameraFunctions.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/ClearColor.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/CommonBufferSourceNames.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/CSGExampleShader.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/CSGObject.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/DefaultShaderFactory.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/DefaultShaderIdentifiers.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/IShaderFactory.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/LightingFunctions.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/Mandelbrot.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/MaterialInterface.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/MathFunctions.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/MicrofacetReflection.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/PhongMaterial.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/ScreenSpaceTriangle.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/SDFObject.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/ShaderID.h
                                      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVShaderFactory/SimpleCSGRayMarching.h)

    set_target_properties(libSPEARShaderFactory PROPERTIES PUBLIC_HEADER "${SPEAR_SHADER_FACTORY_INCLUDES}")
    # IDK if the ShaderFactory is something that should be installed in the $PATH, but let's do that now.
    install(TARGETS libSPEARShaderFactory LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                                          PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

if (SPEAR_BUILD_TESTBED)
    add_executable(SPEARGenTest ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGenTest/main.cpp)
    target_include_directories(SPEARGenTest PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGenTest
                                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hlx/include
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/SPIRVGen
                                                    ${Vulkan_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
    target_link_libraries(SPEARGenTest libSPEARGen ${Vulkan_LIBRARY})
    # Install the testbed as well. This is just for CMakeLists completeness.
    install(TARGETS SPEARGenTest RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
