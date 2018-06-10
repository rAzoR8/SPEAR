//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_DEFAULTFACTORY_H
#define SPEAR_DEFAULTFACTORY_H

#include "IShaderFactory.h"
#include <unordered_map>

namespace Spear
{
	class DefaultShaderFactory : public IShaderFactory
	{
	public:
		DefaultShaderFactory();
		~DefaultShaderFactory();

		SPIRVModule GetModule(const ShaderID _ShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) final;
		void Release() final;

		PLUGIN_INTERFACE(DefaultShaderFactory, 2u);
	private:

		SPIRVModule Compile(const ShaderID _ShaderIdentifier) const;

	private:
		std::unordered_map<uint64_t, SPIRVModule> m_Modules;
	};

	PLUGIN_ALIAS(Spear::DefaultShaderFactory::GetPlugin)
} // Spear

#endif // !SPEAR_DEFAULTFACTORY_H
