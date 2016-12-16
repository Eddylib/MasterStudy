#include <iostream>
#include <iterator>
//#include "accu_traits_func.hpp"
#include <traits_wrap_in_class.hpp>
using namespace std;
class IntClass{
public:
    IntClass(int va):value(va){}
    IntClass(IntClass& va){value=va.getvalue();}
    int getvalue(){return value;}
private:
    int value;
};
const IntClass global(4);
class UseIntClass{
public:
    //constexpr static IntClass iner=global;
};
//const static IntClass UseIntClass::iner = IntClass::IntClass(4);
int main(int argc, char *argv[])
{
    int num[] = {1,2,3,4,5};
    cout<< accum2(&num[0],&num[5])/5 <<endl;
    //cout<< UseIntClass::iner.getvalue() <<endl;
    return 0;
}
