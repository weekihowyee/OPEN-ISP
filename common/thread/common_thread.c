#include "common_thread.h"
#include "stdio.h"

#define DEBUG_THREAD 1

int common_thread_handler(thread_private_t * thrd)
{
   if(thrd->cb== NULL)
   	return -1;
   if(DEBUG_THREAD)
   	printf("common handle thread!\n");
   thrd->cb();
}

int common_thread_start(thread_private_t * thrd)
{
	int rc = 0;
    pthread_t thread_t;

	pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	rc = pthread_create(&thread_t,&attr,common_thread_handler,thrd);  //create consumer thread
	if(DEBUG_THREAD)
		printf("thread create ,rc %d,handler %p\n",rc,common_thread_handler);
}

int common_thread_init(thread_private_t *thrd,thread_type_t type,void *handle_func)
{
	if(thrd == NULL){
		printf("NULL thread!");
		return -1;
	}
	
	pthread_mutex_init(&thrd->msg_q_lock, NULL);
	pthread_cond_init(&thrd->thread_cond, NULL);
	thrd->thread_prop.thread_type = type;
	thrd->cb= handle_func;
    if(DEBUG_THREAD)
		printf("thread init , type %d,handler %p\n",type,handle_func);
	return 0;
}

