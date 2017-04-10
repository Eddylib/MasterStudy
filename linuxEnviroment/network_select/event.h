#ifndef __EVENT_H__
#define __EVENT_H__

#include <poll.h>
#define MAX_QUEUE 1024
enum IDENTIFY {
    ACCEPT_FD,WORK_FD
};
struct EventPoll;
struct Event{
    int index; //index in poll and should not be changed outside.

    /* functional variables below */
    int id;
    void (*r_handler)(struct EventPoll *,struct Event*);
    void (*w_handler)(struct EventPoll *,struct Event*);
    enum IDENTIFY identify;
};
int get_global_eventid(){
    static id = 0;
    return id++;
}
struct EventPoll{
    //for poll function
    struct pollfd pollattr[MAX_QUEUE];

    //fd crossponding events
    struct Event *events[MAX_QUEUE];


    char used[MAX_QUEUE];
    int last_used_index;
    int count;
};
int init_poll(struct EventPoll *pollptr){
    int i = 0;
    if(!(pollptr)){
        return -1;
    }
    for(i = 0; i < MAX_QUEUE; i++){
        pollptr->pollattr[i].fd = 0;
        pollptr->pollattr[i].events = 0;
        pollptr->pollattr[i].revents = 0;
        pollptr->events[i] = (struct Event *)0;
        pollptr->used[i] = 0;
    }
    pollptr->last_used_index = -1;
    pollptr->count = 0;
}
int push_event_poll(struct EventPoll *pollptr,struct Event *event,struct pollfd pfd){
    //inpoll: just insert the event to the tail of the queue
    int index;
    if(!(pollptr && event)){
        return -1;
    }
    if(pollptr->count >= MAX_QUEUE){
        return -2;
    }
    index = pollptr->last_used_index + 1;
    event->index = index;
    pollptr->pollattr[index] = pfd;
    pollptr->events[index] = event;
    pollptr->used[index] = 1;
    pollptr->last_used_index = index;
    ++(pollptr->count);
    return 0;
}
int pop_event_poll(struct EventPoll *pollptr,int event_dequeue){
    //outpoll: extract the event, mv the last event here
    if(!(pollptr)){
        return -1;
    }
    if(pollptr->count <= 0 || event_dequeue > pollptr->last_used_index){
        return -2;
    }
    if(event_dequeue == pollptr->last_used_index){
        pollptr->used[event_dequeue] = 0;
    }else{
        pollptr->pollattr[event_dequeue] = pollptr->pollattr[pollptr->last_used_index];
        pollptr->events[event_dequeue] = pollptr->events[pollptr->last_used_index];

        pollptr->events[event_dequeue]->index = event_dequeue;

        pollptr->used[pollptr->last_used_index] = 0;
    }
    pollptr->last_used_index--;
    pollptr->count--;
    //free event
    return 0;
}
int pop_event_poll_byptr(struct EventPoll *pollptr,struct Event *event){
    if(event&&pollptr)
        return pop_event_poll(pollptr,event->index);
    else
        return -1;
}
#endif
