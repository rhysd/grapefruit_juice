#ifndef __LINDAPP_SINGLETON_HPP__
#define __LINDAPP_SINGLETON_HPP__

namespace lindapp {

    template< class T >
    class singleton {
    private:
        singleton() = default;
        T value;
    public:
        singleton(singleton const&) = delete;
        singleton operator=(singleton const&) = delete;
        singleton(singleton &&) = delete;

        static T &get()
        {
            static singleton<T> s;
            return s.value;
        }
    };

}

#endif // __LINDAPP_SINGLETON_HPP__
