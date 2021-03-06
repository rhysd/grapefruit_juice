#ifndef LINDAPP_SINGLETON_HPP
#define LINDAPP_SINGLETON_HPP

// 指定した型のシングルトンオブジェクトを生成．
// 型Tに対して，singleton<T> はプログラム中に1つしかないことを保証する．
// singleton<T>::get() でアクセス
//
// GCC ではローカルな static 変数へのアクセスは排他制御されるのでマルチスレッドにおける安全性を担保
// http://d.hatena.ne.jp/yohhoy/20120309

namespace gfj{

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

#endif // LINDAPP_SINGLETON_HPP
