//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVEXTENSIONAMD_H
#define SPEAR_SPIRVEXTENSIONAMD_H

#include "SPIRVOperatorImpl.h"

namespace Spear
{
	namespace ExtAMD
	{
		//https://www.khronos.org/registry/spir-v/extensions/AMD/SPV_AMD_gcn_shader.html

		static const std::string ExtGCNShader = "SPV_AMD_gcn_shader";
		enum EGCNShader
		{
			kGCNShader_CubeFaceCoordAMD = 2,
			kGCNShader_CubeFaceIndexAMD = 1,
			kGCNShader_TimeAMD = 3,
		};

		namespace GCNShader
		{
			//The function cubeFaceCoordAMD returns a two-component floating point vector that represents the 2D texture coordinates that would be used for accessing the selected cube map face for the given cube map texture coordinates given as parameter P.
			template <bool Assemble, spv::StorageClass Class>
			inline var_t<float2_t, Assemble, spv::StorageClassFunction> CubeFaceCoord(const var_t<float3_t, Assemble, Class>& _Point)
			{
				// TODO: implement uv lookup
				const auto facecoord = [](const float3_t& p) -> float2_t
				{
					return { 0.f, 0.f };
				};

				return make_ext_op1(_Point, facecoord, ExtGCNShader, kGCNShader_CubeFaceCoordAMD);
			}

			//The function CubeFaceIndexAMD returns a single floating point value that represents the index of the cube map face that would be accessed by texture lookup functions for the cube map texture coordinates given as parameter. The returned value correspond to cube map faces as follows:
			template <bool Assemble, spv::StorageClass Class>
			inline var_t<float, Assemble, spv::StorageClassFunction> CubeFaceIndex(const var_t<float3_t, Assemble, Class>& _Point)
			{
				// TODO: implement index lookup
				const auto faceindex = [](const float3_t& p) -> float
				{
					return 0.f;
				};

				return make_ext_op1(_Point, faceindex, ExtGCNShader, kGCNShader_CubeFaceIndexAMD);
			}

			//The timeAMD function returns a 64-bit value representing the current execution clock as seen by the shader processor. Time monotonically increments as the processor executes instructions. The returned time will wrap after it exceeds the maximum value representable in 64 bits. The units of time are not defined and need not be constant. Time is not dynamically uniform. That is, shader invocations executing as part of a single draw or dispatch will not necessarily see the same value of time. Time is also not guaranteed to be consistent across shader stages. For example, there is no requirement that time sampled inside a fragment shader invocation will be greater than the time sampled in the vertex that lead to its execution.
			template <bool Assemble, class CPUClockType = std::chrono::system_clock>
			inline var_t<int64_t, Assemble, spv::StorageClassFunction> Time()
			{
				const auto time = []() -> int64_t
				{
					return static_cast<int64_t>(CPUClockType::now().time_since_epoch().count());
				};

				return make_ext_op0<Assemble>(time, ExtGCNShader, kGCNShader_TimeAMD);
			}
		}
	} // extamd
} // Spear

#endif // !SPEAR_SPIRVEXTENSIONAMD_H
