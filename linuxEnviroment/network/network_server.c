#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include "config.h"
#define RD_BUFF_SIZE 1024
char rdbf[RD_BUFF_SIZE];
void p(){
    printf("hello world\n");
}
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen){
    int fd;
    int err = 0;

    if((fd = socket(addr->sa_family,type,0)) < 0)
        return -1;
    if((bind(fd, addr, alen)) < 0)
        goto errout;
    if(type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if(listen(fd, qlen) < 0) {
            goto errout;
        }
    }
    return fd;
    errout:
        err = errno;
        close(fd);
        errno = err;
        return -1;
}
void serve(int clientfd){
    send(clientfd,"hello client",strlen("hello client")+1,0);
    recv(clientfd,rdbf,RD_BUFF_SIZE,0);
    printf("read from client: %s\n",rdbf);
    fflush(stdout);
}
int accept_connection(int sockfd,struct sockaddr *_addr,socklen_t *_addr_len){
    int retfd;
    while (1) {
        printf("begin to accept\n");
        fflush(stdout);
        if((retfd = accept(sockfd,_addr,_addr_len)) < 0){
            printf("error to accept: %s\n",strerror(errno));
            fflush(stdout);
        }else{
            serve(retfd);
        }
    }
}
int main(){
    struct socket_parm *serverparm = get_serverparm();
    int serverfd = initserver(serverparm->type,
                              (struct sockaddr *)&serverparm->socket,
                              (socklen_t)sizeof(serverparm->socket),10+03);
    accept_connection(serverfd,NULL,NULL);
}
