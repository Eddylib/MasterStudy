#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <string>
#include <stdio.h>
using namespace std;
boost::mutex io_mutex;
void hello()
{
    boost::mutex::scoped_lock(io_mutex);
    std::cout<<"function started thread: hello"<<std::endl;
}
void function_for_bind(int a,int b,int c){
    static int staCount;
    boost::mutex::scoped_lock(io_mutex);
    cout<<"function_for_bind, a is : "<<a<<" b is : "<<b<<" c is : "<<c<<endl;
    cout<<"this function called: "<<staCount<<" times."<<endl;
}
class ThreadClass{
public:
    ThreadClass(int id):id(id){}
    int getId(){return id;}
    void operator ()(){
        boost::mutex::scoped_lock(io_mutex);
        std::cout<<"class started thread: my id is "<<id<<std::endl;
    }
private:
    int id;
};
class ThreadInClass{
public:
    ThreadInClass(string iname):name(iname),count(0),threadPtr(nullptr){}
    void start(){
        auto f = bind(function_for_bind,3,3,5);
        //bind(&ThreadInClass::simpleFuncStatic,_1,_1,_1)(110);
        //bind(&ThreadInClass::simpleFunc,this,_1,_1,_2)(1,2);
        boost::thread thrd(f);
        threadPtr = &thrd;
    }
    void info(){
        boost::mutex::scoped_lock(io_mutex);
        cout<<"my name is "<<name<<"."<<endl;
    }
    void simpleFunc(int a,int b,int c){
        boost::mutex::scoped_lock(io_mutex);
        cout<<"simple func, a is : "<<a<<" b is : "<<b<<" c is : "<<c<<endl;
        cout<<"this function called: "<<count<<" times."<<endl;
    }
    static void simpleFuncStatic(int a,int b,int c){
        static int staCount;
        boost::mutex::scoped_lock(io_mutex);
        cout<<"simple static func, a is : "<<a<<" b is : "<<b<<" c is : "<<c<<endl;
        cout<<"this function called: "<<staCount<<" times."<<endl;
    }
    void join(){
        if(threadPtr)
            threadPtr->join();
    }
private:
    string name;
    int count;
    boost::thread *threadPtr;
};
int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    //while instance is initialled the thread begins

    //create thread with function
    boost::thread fun_start(&hello);
    //create thread with class instance
    boost::thread instance_start(ThreadClass(110));
    ThreadInClass a(string("libaoyu"));
    a.start();

    fun_start.join();
    instance_start.join();
    return 0;
}
