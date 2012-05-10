#if !defined LINDAPP_IO_HPP_INCLUDED__
#define LINDAPP_IO_HPP_INCLUDED__

#include <iostream>

namespace gfj{

template< class Container >
void print_cs( Container const& container )
{
    for(auto const& i : container){
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template < class Container, class... Containers >
void print_cs( Container const& head, Containers const& ... rest)
{
    print_cs( head );
    print_cs( rest... );
}

void puts()
{
    std::cout << std::endl;
}

template < class... Args >
void puts( Args &&... args )
{
    for( auto && arg : {args...} ){
        std::cout << arg << std::endl;
    }
}

}
#endif // LINDAPP_IO_HPP_INCLUDED__
