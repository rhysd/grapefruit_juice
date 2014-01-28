#if !defined GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED
#define      GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED

#define BOOST_PP_VARIADICS
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define GFJ_LAMBDA_IMPL(r, data, i, elem) auto const& elem\
  BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(data, i))

#define GFJ_LABMDA(...) [&](\
  BOOST_PP_SEQ_FOR_EACH_I(GFJ_LAMBDA_IMPL,\
  BOOST_PP_DEC(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),\
  BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

#ifndef GFJ_DO_NOT_DEFINE_LOWERCASE_LAMBDA
#  define lambda(...) GFJ_LAMBDA(__VA_ARGS__)
#endif

#endif    // GRAPE_FRUIT_JUICE_LAMBDA_MACRO_HPP_INCLUDED
