#if !defined GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED
#define      GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED

// IS_EMPTY() from http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
#define GFJ_AUX_HAS_COMMA_I(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) a15
#define GFJ_AUX_HAS_COMMA(...) GFJ_AUX_HAS_COMMA_I(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define GFJ_AUX_TRIGGER_PARENTHESIS(...) ,
 
#define GFJ_AUX_IS_EMPTY(...) \
GFJ_AUX_IS_EMPTY_I(GFJ_AUX_HAS_COMMA(__VA_ARGS__), \
           GFJ_AUX_HAS_COMMA(GFJ_AUX_TRIGGER_PARENTHESIS __VA_ARGS__), \
           GFJ_AUX_HAS_COMMA(__VA_ARGS__ (/*empty*/)), \
           GFJ_AUX_HAS_COMMA(GFJ_AUX_TRIGGER_PARENTHESIS __VA_ARGS__ (/*empty*/)))
 
#define GFJ_AUX_CAT5(a0, a1, a2, a3, a4) a0 ## a1 ## a2 ## a3 ## a4
#define GFJ_AUX_IS_EMPTY_I(a0, a1, a2, a3) GFJ_AUX_HAS_COMMA(GFJ_AUX_CAT5(GFJ_AUX_IS_EMPTY_CASE_, a0, a1, a2, a3))
#define GFJ_AUX_IS_EMPTY_CASE_0001 ,
 
#define GFJ_AUX_VARIADIC_SIZE(...) GFJ_AUX_VARIADIC_SIZE_I(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#define GFJ_AUX_VARIADIC_SIZE_I(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, size, ...) size
 
#define GFJ_LAMBDA_AUX_16(a, ...) auto const& a, GFJ_LAMBDA_AUX_15(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_15(a, ...) auto const& a, GFJ_LAMBDA_AUX_14(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_14(a, ...) auto const& a, GFJ_LAMBDA_AUX_13(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_13(a, ...) auto const& a, GFJ_LAMBDA_AUX_12(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_12(a, ...) auto const& a, GFJ_LAMBDA_AUX_11(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_11(a, ...) auto const& a, GFJ_LAMBDA_AUX_10(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_10(a, ...) auto const& a, GFJ_LAMBDA_AUX_9(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_9(a, ...)  auto const& a, GFJ_LAMBDA_AUX_8(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_8(a, ...)  auto const& a, GFJ_LAMBDA_AUX_7(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_7(a, ...)  auto const& a, GFJ_LAMBDA_AUX_6(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_6(a, ...)  auto const& a, GFJ_LAMBDA_AUX_5(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_5(a, ...)  auto const& a, GFJ_LAMBDA_AUX_4(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_4(a, ...)  auto const& a, GFJ_LAMBDA_AUX_3(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_3(a, ...)  auto const& a, GFJ_LAMBDA_AUX_2(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_2(a, ...)  auto const& a, GFJ_LAMBDA_AUX_1(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_1(a)       auto const& a
 
#define GFJ_LAMBDA(...) GFJ_LAMBDA_AUX_III(GFJ_AUX_IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)
#define GFJ_LAMBDA_AUX_III(b) GFJ_LAMBDA_AUX_IIII(b)
#define GFJ_LAMBDA_AUX_IIII(b) GFJ_LAMBDA_AUX_ARGS_##b
#define GFJ_LAMBDA_AUX_ARGS_1 GFJ_LAMBDA_AUX_0
#define GFJ_LAMBDA_AUX_ARGS_0(...) GFJ_LAMBDA_AUX_0(GFJ_LAMBDA_AUX_I(GFJ_AUX_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define GFJ_LAMBDA_AUX_I(n) GFJ_LAMBDA_AUX_II(n)
#define GFJ_LAMBDA_AUX_II(size) GFJ_LAMBDA_AUX_##size
#define GFJ_LAMBDA_AUX_0 [&]

#ifdef GFJ_DEFINE_LOWERCASE_LAMBDA
#  define lambda(...) GFJ_LAMBDA(__VA_ARGS__)
#endif

#endif    // GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED
