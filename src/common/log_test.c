#include <stdio.h>
#include <pthread.h>

#include "log.h"

void *
logmsg(void *param)
{
    pthread_setspecific(log_id, param);
    printf("lod id: %d\n", (int)pthread_getspecific(log_id));
    LOG_MSG("thread: %d logging\n", (int)param);
}

int
main(int argc, char **argv)
{
    int ret;
    ret = init_logger("./logtest", 0);
    if (ret) {
        printf("log initialization failed\n");
        return -1;
    }
    pthread_t tid;
    printf("creating child threads\n");
    pthread_create(&tid, NULL, logmsg, (void *)0);
    pthread_create(&tid, NULL, logmsg, (void *)1);
    pthread_create(&tid, NULL, logmsg, (void *)2);
    sleep(10);
    close_logger(3);
    
}
