//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SCREENSPACETRIANGLE_H
#define SPEAR_SCREENSPACETRIANGLE_H

#include "SPIRVProgram.h"
#include "DefaultShaderIdentifiers.h"

namespace Spear
{	
	template <bool Assemble>
	struct SST_VSOUT
	{ 
		var_t<float2_t, Assemble, spv::StorageClassFunction> UVCoords; // if not assigned, the assember will remove the variable from the instruction stream
		var_t<float4_t, Assemble, spv::StorageClassFunction> Position;
	};

	template <bool Assemble>
	inline SST_VSOUT<Assemble> ComputeScreenSpaceTriangle(const var_builtin_t<spv::BuiltInVertexIndex, int, Assemble, spv::StorageClassInput>& _kVertexIndex, const TVertexPermutation _Perm = {})
	{
		using f32 = var_t<float, Assemble, spv::StorageClassFunction>;

		SST_VSOUT<Assemble> VS_OUT;

		f32 x = -1.0f + f32((_kVertexIndex & 1) << 2);
		f32 y = -1.0f + f32((_kVertexIndex & 2) << 1);

		if (_Perm.CheckFlag(kVertexPerm_UVCoords))
		{
			VS_OUT.UVCoords.x = NDCToZeroOne(x);
			VS_OUT.UVCoords.y = NDCToZeroOne(y);
		}

		VS_OUT.Position = {x, y, 0.f, 1.f };

		return VS_OUT;
	}

	template <bool Assemble = true>
	class ScreenSpaceTriangle : public VertexProgram<Assemble>
	{
	public:
		ScreenSpaceTriangle(const TVertexPermutation& _Perm) : VertexProgram<Assemble>("ScreenSpaceTriangle"), m_Permutation(_Perm){};
		~ScreenSpaceTriangle() {};

		//https://rauwendaal.net/2014/06/14/rendering-a-screen-covering-triangle-in-opengl/
		inline void operator()()
		{
			f32 x = -1.0f + f32((kVertexIndex & 1) << 2);
			f32 y = -1.0f + f32((kVertexIndex & 2) << 1);

			if (m_Permutation.CheckFlag(kVertexPerm_UVCoords))
			{
				var_out<float2_t> UVCoords;
				UVCoords.x = NDCToZeroOne(x);
				UVCoords.y = NDCToZeroOne(y);
			}

			kPerVertex->kPostion = float4(x, y, 0.f, 1.f);
		}

	private:
		const TVertexPermutation m_Permutation;
	};
} // Spear

#endif // SPEAR_SCREENSPACETRIANGLE_H