#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include "server_jobs.h"
#include "event.h"
#include "config.h"

int main(){
    struct socket_parm *serverparm = get_serverparm();

    int serverfd = initserver(serverparm->type,
                              (struct sockaddr *)&serverparm->socket,
                              (socklen_t)sizeof(serverparm->socket),10+03);
    struct EventPoll poll;


    init_poll(&poll);

    workloop(serverfd,&poll);
}
