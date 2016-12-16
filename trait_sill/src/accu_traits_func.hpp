#ifndef __ACCU_TRATIS_FNC_HPP__
#define __ACCU_TRATIS_FNC_HPP__
#include <traits.hpp>
//use typename after inline to declear that the AccT is a
//TYPE in Accumation, instead of a VAR
template <typename T>
inline  typename AccumationTraits<T>::AccT accum(T const *beg, T const * end){
    typedef typename AccumationTraits<T>::AccT AccT;
    // the type info is extracted by this func.
    //AccT total = AccumationTraits<T>::zero();
    //AccT total = AccumationTraits<T>::zeroi;
    while (beg!=end) {
        total+=*beg;
        ++beg;
    }
    return total;
}
#endif
