#pragma once

#include "List.hpp"

#include <functional>
#include <string_view>
#include <type_traits>

namespace ReflS {

namespace Detail {
	template<typename>
	struct MemberTrait;

	template<typename _MemberType>
	struct MemberTrait<_MemberType*> {
		using Type				= _MemberType;
		using MemberPointerType = _MemberType;

		static constexpr bool IsStatic = true;
	};

	template<typename _ParentType, typename _MemberType>
	struct MemberTrait<_MemberType _ParentType::*> {
		using ParentType		= _ParentType;
		using Type				= _MemberType;
		using MemberPointerType = _MemberType _ParentType::*;

		static constexpr bool IsStatic = false;
	};
} // namespace Detail

template<typename... Ts>
struct List;

template<typename _Name, typename _PointerLambda, typename _AttrList = List<>>
struct Member : Detail::MemberTrait<decltype(_PointerLambda {}())> {
	static constexpr std::string_view Name {_Name::View()};

	constexpr Member(_Name, _PointerLambda, _AttrList = {}) {}
	constexpr Member() = default;

	static constexpr auto GetPointer() { return _PointerLambda {}(); }

	template<typename... Args>
	static constexpr decltype(auto) Invoke(Args&&... args) {
		return std::invoke(GetPointer(), std::forward<Args>(args)...);
	}
};

namespace Detail {
	template<typename T, typename U>
	struct MemberEqualImpl {
		static constexpr bool Value = false;
	};

	template<typename T, typename U>
		requires(T::Name == U::Name && std::is_same_v<typename T::Type, typename U::Type>)
	struct MemberEqualImpl<T, U> {
		static constexpr bool Value = true;
	};

} // namespace Detail

template<typename T, typename U>
inline constexpr bool MemberEqual = Detail::MemberEqualImpl<T, U>::Value;

struct MemberEqualComp {
	template<typename T, typename U>
	constexpr bool operator()(T = {}, U = {}) {
		return MemberEqual<T, U>;
	}
};
} // namespace ReflS