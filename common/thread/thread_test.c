#include "common_thread.h"
#include "stdio.h"

void test_handler()
{
     printf("shit test_handler\n");
}

int main()
{
	thread_private_t thrd;
	common_thread_init(&thrd,THREAD_TYPE_SERVER,test_handler);
	common_thread_start(&thrd);
	sleep(3);
	printf("test_handler %p\n",test_handler);
    return 0;
}

