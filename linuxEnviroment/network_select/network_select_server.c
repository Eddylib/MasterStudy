#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include "server_jobs.h"
#include "config.h"

int main(){
    struct socket_parm *serverparm = get_serverparm();
    int serverfd = initserver(serverparm->type,
                              (struct sockaddr *)&serverparm->socket,
                              (socklen_t)sizeof(serverparm->socket),10+03);
    accept_connection(serverfd,NULL,NULL);
}
