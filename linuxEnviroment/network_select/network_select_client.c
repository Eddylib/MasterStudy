#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include <errno.h>
#define MAXSLEEP 128
#define RD_BUFF_SIZE 1024
int
connect_retry(int domain, int type, int protocol,const struct scokaddr *addr, socklen_t alen){
    int numsec, fd;
    for(numsec = 1; numsec < MAXSLEEP; numsec <<= 1){
        if((fd = socket(domain,type,protocol)) < 0){
            return -1;
        }
        if(connect(fd,addr,alen) == 0) {
            return fd;
        }
        printf("connect error: %s. Retry...\n",strerror(errno));
        fflush(stdout);
        close(fd);
        if(numsec <= MAXSLEEP/2){
            sleep(numsec);
        }
    }
    return -1;
}
int main(){

    struct socket_parm *clientparm = get_serverparm();
    int sfd;
    char rbuf[RD_BUFF_SIZE];
    if((sfd = connect_retry(clientparm->domain,
                     clientparm->type,
                     clientparm->protocol,
                     (struct sockaddr *)&clientparm->socket,
                     (socklen_t)sizeof(clientparm->socket))) <= 0){
        printf("faild to connect server");
    }else{
        read(sfd,rbuf,RD_BUFF_SIZE);
        printf("read message from server: %s\n",rbuf);
        write(sfd,"hello server",strlen("hello server"));
    }

}
