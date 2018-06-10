//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVCONSTANT_H
#define SPEAR_SPIRVCONSTANT_H

#include "SPIRVType.h"

namespace Spear
{	
	class SPIRVConstant
	{
	public:
		explicit SPIRVConstant(
			const spv::Op _kConstantType = spv::OpConstantNull,
			const SPIRVType& _CompositeType = {},
			const std::vector<uint32_t>& _Constants = {});

		explicit SPIRVConstant(
			const spv::Op _kConstantType,
			const SPIRVType& _CompositeType,
			const std::vector<SPIRVConstant>& _Components);

		~SPIRVConstant();		

		template<class Container, class T = typename Container::value_type>
		static SPIRVConstant MakeVec(const Container& _Elements, const bool _bSpec = false);

		// null
		inline static SPIRVConstant Make() { return SPIRVConstant(spv::OpConstantNull); };

		// primitive
		template<class T>
		static SPIRVConstant Make(const T& _const, const bool _bSpec = false);

		SPIRVConstant(const SPIRVConstant& _Other);

		size_t GetHash(const bool _bParent = true) const;

		const spv::Op& GetType() const noexcept;
		const SPIRVType& GetCompositeType() const noexcept;
		const std::vector<uint32_t>& GetLiterals() const noexcept;
		const std::vector<SPIRVConstant>& GetComponents() const noexcept;

	private:
		spv::Op m_kConstantType = spv::OpNop;

		std::vector<SPIRVConstant> m_Components;

		SPIRVType m_CompositeType;
		std::vector<uint32_t> m_Constants; // binary data
	};

	inline bool operator==(const SPIRVConstant& l, const SPIRVConstant& r)
	{
		return l.GetHash() == r.GetHash();
	}

	inline bool operator!=(const SPIRVConstant& l, const SPIRVConstant& r)
	{
		return l.GetHash() != r.GetHash();
	}

	inline const spv::Op& SPIRVConstant::GetType() const noexcept
	{
		return m_kConstantType;
	}
	inline const SPIRVType& SPIRVConstant::GetCompositeType() const noexcept
	{
		return m_CompositeType;
	}
	inline const std::vector<uint32_t>& SPIRVConstant::GetLiterals() const noexcept
	{
		return m_Constants;
	}
	inline const std::vector<SPIRVConstant>& SPIRVConstant::GetComponents() const noexcept
	{
		return m_Components;
	}

	//---------------------------------------------------------------------------------------------------

	inline size_t LiteralCount(const size_t uSizeInBytes) noexcept
	{
		if (uSizeInBytes % sizeof(uint32_t) == 0)
		{
			return uSizeInBytes / sizeof(uint32_t);
		}
		else
		{
			return static_cast<size_t>(std::ceil(uSizeInBytes / static_cast<float>(sizeof(uint32_t))));
		}
	}

	inline std::vector<uint32_t> MakeLiteralString(const std::string& _sString)
	{
		struct chars
		{
			char elem[sizeof(uint32_t)];
		};

		std::vector<uint32_t> Literals(LiteralCount(_sString.size()), 0u);

		uint32_t i = 0u;
		for (const char& c : _sString)
		{
			chars& chunk = reinterpret_cast<chars&>(Literals[i / sizeof(uint32_t)]);
			chunk.elem[i % sizeof(uint32_t)] = c;
			++i;
		}

		// add string terminator
		if (i % sizeof(uint32_t) == 0u)
		{
			Literals.push_back(0u);
		}

		return Literals;
	}

	//---------------------------------------------------------------------------------------------------
	
	// Helper
	template<class T, class ...Ts>
	inline std::vector<uint32_t> MakeLiterals(const T& _Constant, const Ts& ..._args)
	{
		// TODO: check if T is a std::string and call MakeLiteralString

		// compute number of uint32_t chunks needed to represent the constants
		const size_t uCount = std::max<size_t>(LiteralCount(sizeof(T)), 1ull);
		std::vector<uint32_t> ConstData(uCount, 0u);
		std::memcpy(ConstData.data(), &_Constant, sizeof(T));

		if constexpr(sizeof...(_args) > 0u)
		{
			auto&& vec = MakeLiterals(_args...);
			ConstData.insert(ConstData.end(), vec.begin(), vec.end());
		}

		return ConstData;
	}

	//---------------------------------------------------------------------------------------------------

	template<class Container, class T>
	inline SPIRVConstant SPIRVConstant::MakeVec(const Container& _Elements, const bool _bSpec)
	{
		std::vector<SPIRVConstant> Components;
		for (const T& c : _Elements)
		{
			Components.emplace_back(Make(c, _bSpec));
		}

		return SPIRVConstant(
			_bSpec ? spv::OpSpecConstantComposite : spv::OpConstantComposite,
			SPIRVType::Vec<T>(static_cast<uint32_t>(_Elements.size())),
			Components);
	}

	template<class T>
	inline SPIRVConstant SPIRVConstant::Make(const T& _const, const bool _bSpec)
	{
		constexpr bool SupportedType = std::is_same_v<T, bool> || is_scalar<T> || is_vector<T> || is_matrix<T>;
		static_assert(SupportedType, "Type not supported for spirv constant");

		// TODO: implement arrays!

		if constexpr(std::is_same_v<T, bool>)
		{
			if (_bSpec)
				return SPIRVConstant(_const ? spv::OpSpecConstantTrue : spv::OpSpecConstantFalse);
			else
				return SPIRVConstant(_const ? spv::OpConstantTrue : spv::OpConstantFalse);
		}
		else if constexpr(is_scalar<T>)
		{
			return SPIRVConstant(
				_bSpec ? spv::OpSpecConstant : spv::OpConstant,
				SPIRVType::FromType<T>(),
				MakeLiterals(_const));
		}
		else if constexpr(is_vector<T>)
		{
			constexpr uint32_t N{ Dimension<T> };
			std::vector<SPIRVConstant> Components; // elements
			for (uint32_t i = 0; i < N; ++i)
			{
				Components.emplace_back(Make(_const[i], _bSpec)); // not sure if spec needs to be propagated
			}

			return SPIRVConstant(
				_bSpec ? spv::OpSpecConstantComposite : spv::OpConstantComposite,
				SPIRVType::FromType<T>(),
				Components);
		}
		else if constexpr(is_matrix<T>)
		{
			constexpr uint32_t N = mat_dim<T>::Rows;
			std::vector<SPIRVConstant> Components; // cols
			for (uint32_t i = 0; i < N; ++i)
			{
				Components.emplace_back(Make(_const[i], _bSpec)); // not sure if spec needs to be propagated
			}

			return SPIRVConstant(
				_bSpec ? spv::OpSpecConstantComposite : spv::OpConstantComposite,
				SPIRVType::FromType<T>(),
				Components);
		}
		else
		{		
			return SPIRVConstant(spv::OpConstantNull);
		}
	}

}; // Spear

#endif // !SPEAR_SPIRVCONSTANT_H
