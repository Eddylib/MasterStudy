#ifndef _NET_WORK_CONFIG_H_
#define _NET_WORK_CONFIG_H_
#include <sys/socket.h>
#include <arpa/inet.h>
#include<string.h>

struct socket_parm{
    struct sockaddr_in socket;
    int domain;
    /* AF_INET      ipv4 net domain
     * AF_INET6     ipv6
     * AF_UNIX      UNIX domain
     * AF_UNSPEC    unspecified "any"
    */
    int type;
    /* SOCK_DGRAM           fixed-length, connectionless, unrealiable messages
     * SOCK_RAW             datagram interface to IP
     * SOCK_SEQPACKET       fixed-length, squenced, reliable, connection-oriented messages
     * SOCK_STREAM          sequenced, reliable, bidrectional, connection-oriented byte messages
    */
    int protocol;   //protocol is usually set to zero, to use default protocol for specificed domain and type
    /* IPPROTO_IP
     * IPPROTO_IPV6
     * IPPROTO_ICMP
     * IPPROTO_RAW      this means you need to build your own protocol headers
     * IPPROTO_TCP
     * IPPROTO_UDP
    */
};
struct socket_parm *get_serverparm(){

    static struct socket_parm server;
    static struct sockaddr_in ina;

    bzero(&ina,sizeof(ina));
    ina.sin_family=AF_INET;
    ina.sin_port=htons(1111);
    ina.sin_addr.s_addr = inet_addr("127.0.0.1");

    server.domain = AF_INET;
    server.protocol = IPPROTO_TCP;
    server.socket = ina;
    server.type = SOCK_STREAM;

    return &server;
}
struct socket_parm *get_clientparm(){

    static struct socket_parm client;
    static struct sockaddr_in ina;

    bzero(&ina,sizeof(ina));
    ina.sin_family=AF_INET;
    ina.sin_port=htons(1112);
    ina.sin_addr.s_addr = inet_addr("127.0.0.1");

    client.domain = AF_INET;
    client.protocol = IPPROTO_TCP;
    client.socket = ina;
    client.type = SOCK_STREAM;

    return &client;
}
#endif
