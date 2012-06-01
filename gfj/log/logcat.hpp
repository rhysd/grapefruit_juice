#if !defined LINDAPP_LOGCAT_HPP_INCLUDED__
#define LINDAPP_LOGCAT_HPP_INCLUDED__

#include <iostream>

namespace gfj{

template <class EFunc, class WFunc, class VFunc, class OStream>
class logcat{
    EFunc ewriter;
    WFunc wwriter;
    VFunc vwriter;
    OStream output;
public:

   logcat( EFunc && ew = []{return "";},
            WFunc && ww = []{return "";},
            VFunc && vw = []{return "";},
            OStream && output=std::cerr )
        : ewriter(ew),wwriter(ww),vwriter(vw),output(output)
    {}

    template<class... Args>
    void error(Args &&... args)
    {
        output << "\e[31m*** Error ***\n"
               << ewriter(std::forward<Args>(args)...)
               << "\n*** End ***\e[0m\n";
    }

    template<class... Args>
    void warning(Args &&... args)
    {
        output << "\e[33m*** Warning ***\n"
               << wwriter(std::forward<Args>(args)...)
               << "\n*** End ***\e[0m\n";
    }

    template<class... Args>
    void varbose(Args &&... args)
    {
        output << "\e[32m*** Varbose ***\n"
               << vwriter(std::forward<Args>(args)...)
               << "\n*** End ***\e[0m\n";
    }

    virtual ~logcat(){};
};

template<class E, class W, class V, class O>
logcat<E, W, V, O> make_logcat(E && e = []{return "";},
                               W && w = []{return "";},
                               V && v = []{return "";},
                               O && o = std::cerr)
{
    return { std::forward<E>(e), std::forward<W>(w), std::forward<V>(v), std::forward<O>(o) };
}

} // gfj

#endif // LINDAPP_LOGCAT_HPP_INCLUDED__
