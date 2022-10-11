#pragma once

#include <string_view>

namespace ReflS {

template<typename>
struct TypeInfo;

template<typename _AttrLambda>
struct Attribute {
	constexpr Attribute(_AttrLambda) {}
	constexpr Attribute() = default;

	using Type = decltype(_AttrLambda {}());
	static constexpr auto Get() { return _AttrLambda {}(); }
};

} // namespace ReflS