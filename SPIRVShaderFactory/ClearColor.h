//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_CLEARCOLOR_H
#define SPEAR_CLEARCOLOR_H

#include "SPIRVProgram.h"

namespace Spear
{
	template <bool Assemble = true>
	class ClearColor: public FragmentProgram<Assemble>
	{
	public:
		ClearColor() : FragmentProgram<Assemble>("ClearColor") {};
		~ClearColor() {};

		//CBuffer<B> BufferBlock;
		RenderTarget OutputColor;

		inline void operator()()
		{
			OutputColor = float4(1.f, 0.f, 0.0f, 0.f);
		};
	private:
	};

} // Spear

#endif // !SPEAR_CLEARCOLOR_H
