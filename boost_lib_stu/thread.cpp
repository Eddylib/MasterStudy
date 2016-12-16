#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdio.h>
using namespace std;
void hello()
{
    std::cout<<"thread func"<<std::endl;
}
int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    boost::thread thrd(&hello);
    thrd.join();
    fgetc(stdin);
    return 0;
}
