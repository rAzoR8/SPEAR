//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_DEFAULTSHADERIDENTIFIERS_H
#define SPEAR_DEFAULTSHADERIDENTIFIERS_H

#include "ShaderID.h"
#include <Flag.h>

namespace Spear 
{
	enum EDefaultShader : uint16_t
	{
		kDefaultShader_ClearColor,
		kDefaultShader_ScreenSpaceTriangle,
		kDefaultShader_Mandelbrot,
		kDefaultShader_CSGExample
	};

	enum EVertexPerm : uint32_t
	{
		kVertexPerm_None = 0,
		kVertexPerm_UVCoords = 1 << 0,
	};

	using TVertexPermutation = hlx::Flag<EVertexPerm>;

	constexpr ShaderID kShader_ScreenSpaceTriangle = kShaderID<kShaderType_Vertex, kDefaultShader_ScreenSpaceTriangle>;
	constexpr ShaderID kShader_ScreenSpaceTriangle_UV = kShaderID<kShaderType_Vertex, kDefaultShader_ScreenSpaceTriangle, kVertexPerm_UVCoords>;

	constexpr ShaderID kShader_ClearColor = kShaderID<kShaderType_Fragment, kDefaultShader_ClearColor>;
	constexpr ShaderID kShader_Mandelbrot = kShaderID<kShaderType_Fragment, kDefaultShader_Mandelbrot>;
	constexpr ShaderID kShader_CSGExample = kShaderID<kShaderType_Fragment, kDefaultShader_CSGExample>;

} // Spear

#endif // !SPEAR_DEFAULTSHADERIDENTIFIERS_H