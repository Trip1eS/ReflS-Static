#pragma once

#include "Member.hpp"

namespace ReflS {

template<typename _Name, typename _PointerLambda, typename _AttrList = List<>>
struct Field : Member<_Name, _PointerLambda, _AttrList> {
	constexpr Field(_Name, _PointerLambda, _AttrList = {}) {}
	constexpr Field() = default;
};

} // namespace ReflS