/*
This cpp is recorded to learn condition variables.
But during learing the conditon, I found many problems.
Summary here:

1 A condition must exist with a mutex, which is a lock to protect the attrbutes of
  condition.
2 If a condition protect a data struct just in the areas of the condition code. any
  other attributes of the dada struct must be proected with other measures.(here i
  used a queue in std lib. the push and pop can be protected but the attr of the queue
  itself not. So, the attr lock did this. If I build a thread safe queue, there is no
  need of the attrlock)
3 for multy readers and writers, the if must be changed to where when judge either the queue
  is full or empty.

*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <queue>
#include <vector>
using namespace std;
boost::mutex mutex;
class Product{
public:
    Product(int maxsize):_maxSize(maxsize){}
    void makeOne(int m){
        boost::mutex::scoped_lock lock(condlock);
        attrlock.lock();
        while(_product.size() >= _maxSize){
            attrlock.unlock();
            notfull.wait(lock);
        }
        _productPush(m);
        attrlock.unlock();
        notempty.notify_one();
    }
    int getOne(){
        boost::mutex::scoped_lock lock(condlock);
        attrlock.lock();
        int a ;
        while(_product.empty()){
            attrlock.unlock();
            notempty.wait(lock);
        }
        a = _productPop();
        attrlock.unlock();
        notfull.notify_one();
        return a;
    }
    //for external callers
    int num(){
        boost::mutex::scoped_lock lock(attrlock);
        return _product.size();
    }
    bool isEmpty(){
        boost::mutex::scoped_lock lock(attrlock);
        return _product.empty();
    }
    bool isFull(){
        boost::mutex::scoped_lock lock(attrlock);
        return _product.size() >= _maxSize;
    }
private:
    boost::mutex condlock;
    boost::condition notfull;
    boost::condition notempty;
    boost::mutex attrlock;
    queue<int> _product;
    int _maxSize;
    void _productPush(int add){
            _product.push(add);
    }
    int _productPop(){
        int a;
        a = _product.front();
            _product.pop();
        return a;
    }
    int _productHead(){
        return _product.front();
    }
};
boost::mutex io;

//the monitor mutex not only work for condition variable, but also
//protect the zone operate to the related data
class Provider{
public:
    Provider(Product *buf,float workFrequence):workFrequence(workFrequence){
        _buf = buf;
        number=1;
        _buf->makeOne(number++);
    }
    void operator ()(){threadLoop();}
private:
    float workFrequence;
    int number;
    Product *_buf;
    void sleep(){
        boost::this_thread::sleep(boost::posix_time::seconds(workFrequence));
    }
    void threadLoop(){
        int total;
        while (true) {
            sleep();
            _buf->makeOne(number++);
            total=_buf->num();
            boost::mutex::scoped_lock lockio(io);
            cout<<"thread:"<<boost::this_thread::get_id()
               <<" provide one: "<<number-1
              <<" total:"<<total<<endl;
        }
    }
};
class Consumer{
public:
    Consumer(Product *buf,float workFrequence):workFrequence(workFrequence){_buf = buf;}
    void operator ()(){threadLoop();}
private:
    Product *_buf;
    float workFrequence;
    void sleep(){
        boost::this_thread::sleep(boost::posix_time::seconds(workFrequence));
    }
    void threadLoop(){
        int get;
        int total;
        while (true) {
            sleep();
            get = _buf->getOne();
            total = _buf->num();
            boost::mutex::scoped_lock lockio(io);
            cout<<"thread:"<<boost::this_thread::get_id()
               <<"consume one: "<<get
              <<" total:"<<total<<endl;
        }
    }
};
int main()
{
    Product product(30);
    Provider provider(&product,0);
    Consumer consumer(&product,0);
    vector<boost::thread *> threadpolls;
    threadpolls.push_back(new boost::thread(boost::ref(provider)));
    threadpolls.push_back(new boost::thread(boost::ref(provider)));
    threadpolls.push_back(new boost::thread(boost::ref(provider)));
    threadpolls.push_back(new boost::thread(boost::ref(consumer)));
    for(auto i : threadpolls){
        i->join();
        delete i;
    }
    return 0;
}
