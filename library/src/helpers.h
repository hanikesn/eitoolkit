#ifndef helpers_H
#define helpers_H

#include <memory>

template<typename T, typename ...Args> std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

template <typename Dst, typename Src> std::unique_ptr<Dst> unique_dynamic_cast( std::unique_ptr<Src>& ptr ) {
    Src* p = ptr.release();
    std::unique_ptr<Dst> r( dynamic_cast<Dst*>(p) );
    if ( !r ) {
        ptr.reset( p );
    }
    return r;
}

#endif
