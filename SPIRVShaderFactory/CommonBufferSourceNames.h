//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_COMMONBUFFERSOURCENAMES_H
#define SPEAR_COMMONBUFFERSOURCENAMES_H

#include "CompileTimeString.h"

namespace Spear
{
	namespace BufferSources
	{
		using namespace hlx;

		static constexpr std::string_view sObjectWorldMatrix = "SPEAR_OBJ_WORLD_MATRIX"_sv;
		static constexpr std::string_view sViewProjectionMatrix = "SPEAR_VIEW_PROJ_MATRIX"_sv;
		static constexpr std::string_view sFrameBufferDimension = "SPEAR_FRAMEBUFFER_DIM"_sv;

#pragma warning(push)
#pragma warning(disable: 4307)
		static constexpr uint64_t kObjectWorldMatrix = const_string_hash(sObjectWorldMatrix);
		static constexpr uint64_t kViewProjectionMatrix = const_string_hash(sViewProjectionMatrix);
		static constexpr uint64_t kFrameBufferDimension = const_string_hash(sFrameBufferDimension);
#pragma warning(pop)
	}
} // Spear

#endif // !SPEAR_COMMONBUFFERSOURCENAMES_H
