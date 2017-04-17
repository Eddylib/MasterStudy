# Linux Enviroment Programming

A subdirectory to learn linux features 

* network is the basic network programming
* newwork_select combines network and IO multiplexing.

Notes
------------
在使用poll监听socket时，POLLIN时间的四个来源

* 有数据到达。 
* 一个listen的fd上有连接进入，这时候对这个fd调用accept不会被阻塞。
* socket发生错误。对该fd 调用recv 会返回-1.
* fd被shutdown, 对该fd调用 recv 会得到0(EOF)的返回值.


