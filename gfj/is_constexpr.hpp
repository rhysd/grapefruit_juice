#if !defined GRAPEFLUIT_JUICE_CONSTEXPR_CHECKER_HPP_INCLUDED
#define      GRAPEFLUIT_JUICE_CONSTEXPR_CHECKER_HPP_INCLUDED

/*
 *
 * int dynamic_initialization()
 * {
 *   return 42;
 * }
 *
 * int const i = dynamic_initialization();
 * int const j = 42;
 *
 * // O.K. The expression is a constant expression.
 * int const x = ASSERT_CONSTANT_EXPRESSION(j);
 *
 * // Compile error because the expression is not a constant expression.
 * int const y = ASSERT_CONSTANT_EXPRESSION(i);
 *
 */

namespace gfj {

template<class T>
constexpr T is_constant_expression_impl(T x) throw(int)
{
  return x;
}

#define IS_CONSTANT_EXPRESSION(EXPR) noexcept(is_constant_expression_impl(EXPR))

template<bool B, class T>
constexpr T assert_constant_expression_impl(T x)
{
  static_assert(B, "");
  return x;
}

#define ASSERT_CONSTANT_EXPRESSION(EXPR) \
assert_constant_expression_impl<IS_CONSTANT_EXPRESSION(EXPR)>(EXPR)

} // namespace gfj

#endif    // GRAPEFLUIT_JUICE_CONSTEXPR_CHECKER_HPP_INCLUDED
