#ifndef __SERVER_JOBS_H__
#define __SERVER_JOBS_H__
#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#include "config.h"
#include "event.h"
#define RD_BUFF_SIZE 1024
#define MAX_EVENT 100
enum IDENTIFY {
    ACCEPT_FD,WORK_FD
};
struct Event{
    struct pollfd pollattr;
    int work_count;
    enum IDENTIFY identify;
    void (*event_handler)(void *);
};

char rdbf[RD_BUFF_SIZE];
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


void serve(){

}
void readyforwork(){

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
            serve();
        }
    }
}
#endif
