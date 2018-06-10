//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SHADERID_H
#define SPEAR_SHADERID_H

#include <cstdint>
#include <string>

namespace Spear
{
    enum EShaderType : uint8_t
    {
        kShaderType_Vertex = 0,
        kShaderType_TessellationControl = 1,
        kShaderType_TessellationEvaluation = 2,
        kShaderType_Geometry = 3,
        kShaderType_Fragment = 4,
        kShaderType_GLCompute = 5,
        kShaderType_Kernel = 6,

        kShaderType_NumOf,
        kShaderType_Unknown = kShaderType_NumOf
    };

    template <EShaderType kType, uint16_t uShader, uint32_t uVariant = 0u>
    constexpr uint64_t kShaderID = (uint8_t)kType | ((uint64_t)uShader << 16u) | ((uint64_t)uVariant << 32u);

    struct ShaderID
    {
        constexpr ShaderID(const uint64_t _uID = kShaderType_Unknown) : uID(_uID) {}
        constexpr ShaderID(const EShaderType _kType, const uint8_t _uCompileFlags, const uint16_t _uShader, const uint32_t _uVariant) :
            kType(_kType), uCompileFlags(_uCompileFlags), uShader(_uShader), uVariant(_uVariant) {}
        constexpr ShaderID(const ShaderID& _Other) : uID(_Other.uID) {}

        inline std::string GetString() const { return "Type " + std::to_string(kType) + " Shader " + std::to_string(uShader) + " Variant " + std::to_string(uVariant) + " Flags " + std::to_string(uCompileFlags); }

        static constexpr uint64_t kInvalid = kShaderType_Unknown;

        const bool Valid() const { return kType < kShaderType_NumOf; }

        union
        {
            struct
            {
                EShaderType kType; // 8
                uint8_t uCompileFlags; // debug, optimization etc
                uint16_t uShader; // which shader
                uint32_t uVariant; // which permutation of the shader
            };
            uint64_t uID;
        };

        operator uint64_t() const { return uID; }
    };
} // Spear

#endif // !SPEAR_SHADERID_H
