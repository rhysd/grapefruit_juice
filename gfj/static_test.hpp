#ifndef LINDAPP_STATIC_TEST_HPP
#define LINDAPP_STATIC_TEST_HPP

namespace gfj{

    template<class T, T Value, T Min, T Max>
    inline constexpr void assert_out_of_range()
    {
        static_assert(Min<=Value&&Value<=Max, "gfj::assert_out_of_range: failed");
        return;
    }

}

#endif // LINDAPP_STATIC_TEST_HPP
