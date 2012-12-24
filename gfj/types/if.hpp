#if !defined LINDAPP_ENABLE_IF_HPP_INCLUDED
#define LINDAPP_ENABLE_IF_HPP_INCLUDED

#include "type_traits_aliases.hpp"

namespace gfj{

extern void *enabler;

template< bool B, class T >
using disable_if = gfj::enable_if< !B, T >;

template< bool B, class T, class U >
using if_ = gfj::conditional< B, T, U>;

}
#endif // LINDAPP_ENABLE_IF_HPP_INCLUDED
