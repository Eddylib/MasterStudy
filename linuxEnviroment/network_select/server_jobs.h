#ifndef __SERVER_JOBS_H__
#define __SERVER_JOBS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#include "config.h"
#include "event.h"
#define RD_BUFF_SIZE 1024


/*
有4种情况在一个fd上能够得到一个POLLIN事件：
1 有数据到达。
2 fd被shutdown, 对该fd调用 recv 会得到0(EOF)的返回值.
3 一个listen的fd上有连接进入，这时候对这个fd调用accept不会被阻塞。
4 socket发生错误。对该fd 调用recv 会返回-1.
*/
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


void handler_echo(struct EventPoll *pollpt,struct Event*event){
    /* read, write */
    int len;
    char sendbuf[RD_BUFF_SIZE + 100];
    static int usecount = 0;
    printf("--------------------\necho handler\n");
    usecount++;
    if((len = recv(pollpt->pollattr[event->index].fd,rdbf,RD_BUFF_SIZE,0)) > 0){
        printf("Receive a message from client %d, index @ %d:\n %s\n",
               event->id,
               event->index,
               rdbf);
        fflush(stdout);
    }else if(len == 0){
        goto out_shutdown;
    }else {
        goto out_error;
    }


    fflush(stdout);
    sprintf(sendbuf,
            "Hello Client, your ID is %d, your command is: %s\n",
            event->id,
            rdbf);
    if(send(pollpt->pollattr[event->index].fd,
            sendbuf,
            strlen(sendbuf)+1,
            0) == -1){
        printf("error to send\n");
        fflush(stdout);
    }
    rdbf[0] = 0;

out_fflush:
    fflush(stdout);
    return;
out_shutdown:
    printf("client %d shutdown.\n",event->id);
    pop_event_poll_byptr(pollpt,event);
    goto out_fflush;
out_error:
    printf("error.\n");
    goto out_fflush;
}
void handler_accept(struct EventPoll *pollpt,struct Event*event){
    /* create a new event and add to the poll */
    int retfd;
    struct pollfd epfd;
    struct Event *workevent;
    printf("--------------------\naccept handler\n");
    // do not care about client address now
    if((retfd = accept(pollpt->pollattr[event->index].fd,NULL,NULL)) < 0){
        printf("error to accept: %s\n",strerror(errno));
    }else{
        // add it to fd
        epfd.fd = retfd;
        epfd.events = POLLIN;
        epfd.revents = 0;

        if((workevent = (struct Event *)malloc(sizeof(struct Event))) == NULL){
            printf("unable to allocate memery, do not serve this event");
        }
        workevent->id = get_global_eventid();
        workevent->identify = WORK_FD;
        workevent->r_handler=handler_echo;

        push_event_poll(pollpt,workevent,epfd);
    }
}

void workloop(int initfd,struct EventPoll* pollpt){
    struct Event *acceptep, *come = NULL;
    int retv,i;
    if((acceptep = (struct Event *)malloc(sizeof(struct Event))) == NULL){
        printf("unable to allocate memery");
        exit(0);
    }
    acceptep->id = get_global_eventid();
    acceptep->identify = ACCEPT_FD;
    acceptep->r_handler = handler_accept;

    struct pollfd acceptfd = {initfd,POLLIN,0};

    push_event_poll(pollpt,acceptep,acceptfd);
    printf("OK\n");

    while(1){
        printf("-------------\nbegin to poll\n");
        fflush(stdout);
        if((retv = poll(pollpt->pollattr,pollpt->count,-1)) == 0){
            printf("time out!\n");
        }else if(retv != -1){
            printf("%d events.\n",retv);
            for(i=0;i<=pollpt->last_used_index;i++){
                if(pollpt->pollattr[i].revents){
                    if(pollpt->pollattr[i].revents&POLLIN){
                        printf("readable\n");
                        come = pollpt->events[i];
                        come->r_handler(pollpt,come);
                    }
                    /* usually writable */
                    /*if(pollpt->pollattr[i].revents&POLLOUT){
                        printf("writable\n");
                    }*/
                    if(pollpt->pollattr[i].revents&POLLERR){
                        printf("error on event\n");
                    }
                    if(pollpt->pollattr[i].revents&POLLHUP){
                        printf("event end.\n");
                    }
                }
            }
        }else{
            printf("error.\n");
        }
    }
}
#endif
