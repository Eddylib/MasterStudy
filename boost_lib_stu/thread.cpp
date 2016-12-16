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
    //while instance is initialled the thread begins
    boost::thread thrd(&hello);
    thrd.join();
    return 0;
}
