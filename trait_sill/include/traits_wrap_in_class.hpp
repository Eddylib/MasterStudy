#ifndef __TRAITS_2_HPP_
#define __TRAITS_2_HPP_
#include "traits.hpp"
template<typename T,typename AT = AccumationTraits<T> >
class Accum{
public:
    static typename AT::AccT accum(T const *beg, T const *end){
        typename AT::AccT total = AT::zero();
        while (beg!=end) {
            total+=*beg;
            ++beg;
        }
        return total;
    }
};

template <typename T>
inline typename AccumationTraits<T>::AccT accum2(T const *beg, T const *end){
    return Accum<T>::accum(beg,end);
}

template<typename T,typename Traits>
inline typename Traits::AccT accum2(T const *beg, T const *end){
    return Accum<T,Traits>::accum(beg,end);
}
#endif
