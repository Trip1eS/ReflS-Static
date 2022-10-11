#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <string_view>

namespace ReflS {

template<size_t _Size, typename _ValueType = char>
struct StrBase {
	using ValueType				 = _ValueType;
	static constexpr size_t Size = _Size;

	ValueType Data[_Size + 1] {};
	constexpr StrBase(std::basic_string_view<ValueType> str) {
		std::copy_n(str, _Size, Data);
	}
	constexpr StrBase(const char* str) { std::copy_n(str, _Size, Data); }
};

template<size_t _Size, typename _ValueType>
StrBase(const _ValueType (&)[_Size]) -> StrBase<_Size - 1, _ValueType>;

template<StrBase _Str>
struct Str {
	using CharType = typename decltype(_Str)::ValueType;

	static constexpr auto View() { return std::basic_string_view<CharType> {_Str.Data}; }
	static constexpr auto Data() { return _Str.Data; }
	static constexpr auto Size() { return _Str.Size; }
};

} // namespace ReflS