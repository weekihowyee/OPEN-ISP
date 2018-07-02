#ifndef _COMMON_THREAD_H_
#define _COMMON_THREAD_H_

#include <pthread.h>

typedef enum {
  THREAD_TYPE_SERVER,
  THREAD_TYPE_MODULE,
  THREAD_TYPE_PORT,
  THREAD_TYPE_CUSTOM
 } thread_type_t;

typedef struct {
	
  	int thread_id;

  	thread_type_t thread_type; 

}thread_prop_t;


typedef struct {  //thread private data
	
    void *parent;

	pthread_mutex_t msg_q_lock;

	pthread_cond_t  thread_cond;

	thread_prop_t thread_prop;

	void (*cb)();

} thread_private_t;

int common_thread_init(thread_private_t *thrd,thread_type_t type,void *handle_func);
int common_thread_start(thread_private_t * thrd);


#endif

