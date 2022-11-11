#pragma once

#define REFLS_TYPE(TYPE, _BASES, _CTORS, _MEMBERS, ...)             \
	template<>                                                      \
	struct ReflS::TypeInfo<TYPE> {                                  \
		using Type = TYPE;                                          \
		static constexpr std::string_view Name {#TYPE};             \
		static constexpr List			  Attributes {__VA_ARGS__}; \
		_BASES                                                      \
		_CTORS                                                      \
		_MEMBERS                                                    \
	}

#define ATTR(...) Attribute([]() { return __VA_ARGS__; })
#define BASES(...) static constexpr List Bases = MakeBaseList<__VA_ARGS__>;
#define CTORS(...) static constexpr List Constructors {__VA_ARGS__};
#define MEMBERS(...) static constexpr List Members {__VA_ARGS__};
#define CTOR(...) \
	Constructor<Type, __VA_ARGS__> {}
#define DEFAULT_CTOR() \
	Constructor<Type> {}
#define FIELD(NAME, ...)              \
	Field(                            \
		Str<#NAME> {},                \
		[]() { return &Type::NAME; }, \
		List {__VA_ARGS__}            \
	)
#define FUNCTION(NAME, ...)           \
	Function(                         \
		Str<#NAME> {},                \
		[]() { return &Type::NAME; }, \
		List {__VA_ARGS__}            \
	)
#define FUNCTION_OVERLOAD(NAME, FUNC_TYPE, ...)                             \
	Function(                                                               \
		Str<#NAME> {},                                                      \
		[]() -> MemberPointerType<Type, FUNC_TYPE> { return &Type::NAME; }, \
		List {__VA_ARGS__}                                                  \
	)

#if REFLS_PARSER

// some macro magic here
// ref:
// https://github.com/veselink1/refl-cpp/blob/master/include/refl.hpp#L4613

#define REFLS_EXPAND(x) x
#define REFLS_FOR_EACH_0(...)
#define REFLS_FOR_EACH_1(what, x, ...) what(x)
#define REFLS_FOR_EACH_2(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_1(what, __VA_ARGS__))
#define REFLS_FOR_EACH_3(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_2(what, __VA_ARGS__))
#define REFLS_FOR_EACH_4(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_3(what, __VA_ARGS__))
#define REFLS_FOR_EACH_5(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_4(what, __VA_ARGS__))
#define REFLS_FOR_EACH_6(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_5(what, __VA_ARGS__))
#define REFLS_FOR_EACH_7(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_6(what, __VA_ARGS__))
#define REFLS_FOR_EACH_8(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_7(what, __VA_ARGS__))
#define REFLS_FOR_EACH_9(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_8(what, __VA_ARGS__))
#define REFLS_FOR_EACH_10(what, x, ...) \
	what(x) REFLS_EXPAND(REFLS_FOR_EACH_9(what, __VA_ARGS__))

#define REFLS_FOR_EACH_RSEQ_N() 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define REFLS_FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define REFLS_FOR_EACH_NARG(...) \
	REFLS_FOR_EACH_NARG_(__VA_ARGS__, REFLS_FOR_EACH_RSEQ_N())
#define REFLS_FOR_EACH_NARG_(...) REFLS_EXPAND(REFLS_FOR_EACH_ARG_N(__VA_ARGS__))
#define REFLS_CONCAT(x, y) x##y
#define REFLS_FOR_EACH_(N, what, ...) \
	REFLS_EXPAND(REFLS_CONCAT(REFLS_FOR_EACH_, N)(what, __VA_ARGS__))
#define REFLS_FOR_EACH(what, ...) \
	REFLS_FOR_EACH_(REFLS_FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#define Attr_Each(attr) __attribute__((annotate(#attr)))
#define Attr(...) REFLS_FOR_EACH(Attr_Each, __VA_ARGS__)

#else

#define Attr(...)

#endif