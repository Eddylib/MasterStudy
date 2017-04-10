#include <pthread.h>
#include <stdio.h>
/* easy and no need to annotate */
void* thread_func1(void *arg){
    printf("thread_func1\n");
    //pthread_exit((void*)111);
    return (void *)3;
}
void* thread_func2(void *arg){
    printf("thread_func2\n");
    return (void *)1;
}
void check(int err,char *msg){
    if(err){
        printf("error: %s code: %d\n",msg,err);
    }
}
int main()
{
    void *tret;
    int err;
    pthread_t tid1,tid2;
    check(pthread_create(&tid1,NULL,thread_func1,NULL),"thread1");
    check(pthread_create(&tid2,NULL,thread_func2,NULL),"thread2");
    err = pthread_join(tid1,&tret);
    printf("%ld\n",(long)tret);
    pthread_cancel(tid2);
    err = pthread_join(tid2,&tret);
    printf("%ld\n",(long)tret);
    if(PTHREAD_CANCELED == (long)tret){
        printf("PTHRAED_CANCLED is %ld",(long)tret);
    }
    scanf("%d",&err);

}
