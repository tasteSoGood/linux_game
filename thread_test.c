#include <stdio.h>
#include <pthread.h>

void thread(void) {
    int i;
    for(i = 0; i < 10; i++)
        printf("This is a pthread.\n");
}

int main(void){
    pthread_t id;
    int i, ret;
    ret = pthread_create(&id, NULL, (void *)thread, NULL);
    if(ret != 0) {
        printf("Create pthread error！\n");
    }
    for(i = 0; i < 10; i++)
        printf("This is main process.\n");
    pthread_join(id, NULL);
    return 0;
}