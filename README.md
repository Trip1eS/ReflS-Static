# ReflS

ReflS is a small static reflection library for C++20, providing compile-time type information.

## Basic usage

To reflect a simple structure:

```c++
struct Vector2 {
	float x, y;
	float Magnitude() const { return std::sqrt(x * x + y * y); }

	Vector2() : x(.0f), y(.0f) {}
	Vector2(float x_, float y_) : x(x_), y(y_) {}
};
```

### Registration
```c++
template<>
struct ReflS::TypeInfo<Vector2> {
	using Type = Vector2;
	static constexpr std::string_view Name {"Vector2"};
	static constexpr List			  Attributes {};
	static constexpr List			  Bases {};
	static constexpr List			  Constructors {
		Constructor<Type> {},
		Constructor<Type, float, float> {}};
	static constexpr List Members {
		Field(Str<"x"> {}, []() { return &Type::x; }),
		Field(Str<"y"> {}, []() { return &Type::y; }),
		Function(Str<"Magnitude"> {}, []() { return &Type::Magnitude; })};
};
```

### Or register using macros

```c++
REFLS_TYPE(
	Vector2,
	BASES(),
	CTORS(DEFAULT_CTOR(), CTOR(float, float)),
	MEMBERS(FIELD(x), FIELD(y), FUNCTION(Magnitude))
);
```

### Get TypeDescriptor

To get type information of `Vector2`, use `ReflS::TypeDescriptor<Vector2>`.

```c++
ReflS::TypeDescriptor<Vector2> type;
```

### Iterate over members

```c++
type.Members.ForEach([](auto member) {
    std::cout << member.Name << std::endl;
});
```

### Find a member with a specified name

Use `List<Ts...>::Find(Pred)` to find the first element in the list that satisfies the predicate. This is done in compile-time.

```c++
auto func = type.Members.Find([](auto member){
    return member.Name == "Magnitude";
});
```

### Invoke methods / Get or set variables

The `Invoke` method of members is the same as `std::invoke()` without the first argument.

```c++
Vector2 vec(3.0f, 4.0f);
std::cout << func.Invoke(vec) << std::endl;
```