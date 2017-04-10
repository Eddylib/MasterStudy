#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include <errno.h>
#define MAXSLEEP 128
#define RD_BUFF_SIZE 1024
int
connect_retry(int domain,
              int type, int protocol,
              const struct sockaddr *addr,
              socklen_t alen){
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

    struct socket_parm *servertparm = get_serverparm();
    int sfd;
    char rbuf[RD_BUFF_SIZE];
    char wbuf[RD_BUFF_SIZE];
    if((sfd = connect_retry(servertparm->domain,
                     servertparm->type,
                     servertparm->protocol,
                     (struct sockaddr *)&servertparm->socket,
                     (socklen_t)sizeof(servertparm->socket))) <= 0){
        printf("faild to connect server: %s\n",strerror(errno));
    }else{
        while (1) {
            scanf("%s",wbuf);
            write(sfd,wbuf,strlen(wbuf)+1);
            read(sfd,rbuf,RD_BUFF_SIZE);
            printf("read message from server: %s\n",rbuf);
        }
        close(sfd);
    }

}
