#ifndef TRAITS_HPP
#define TRAITS_HPP
#include <iostream>
template<typename T>
class AccumationTraits;

template<>
class AccumationTraits<char>{
public:
    typedef int AccT;
    static AccT zero(){
        return 0;
    }

};
template<>
class AccumationTraits<short>{
public:
    typedef int AccT;
    static AccT zero(){
        return 0;
    }

};/*
class IntClass{
public:
    IntClass operator = (int arg){
        return *this;
    }
   /* IntClass operator =(int arg){
        internal = arg;
        return *this;
    }
    IntClass operator ()(int arg){
        internal = arg;
        return *this;
    }
    IntClass operator +=()(const IntClass &right){
        return *this;
    }
    std::ostream & operator << (const std::ostream &os,IntClass &arg){
        return os<<arg.ingernal;
    }
private:
    int internal;
};*/
template<>
class AccumationTraits<int>{
public:
    typedef int AccT;
    static AccT zero(){
        return 0;
    }
    const static AccT zeroi = 0.0;
};
//const static AccumationTraits<int>::AccT zeroi = 0.0;
#endif // TRAITS_HPP
