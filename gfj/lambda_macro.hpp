#if !defined GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED
#define      GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED

#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define lambda_impl(r, data, i, elem) auto const& elem\
  BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(data, i))

#define lambda(...) [&](\
  BOOST_PP_SEQ_FOR_EACH_I(lambda_impl,\
  BOOST_PP_DEC(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),\
  BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

#endif    // GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED
