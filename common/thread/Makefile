runner: thread_test.o common_thread.o
	gcc -o runner thread_test.o common_thread.o -g  -pthread
thread_test.o: thread_test.c common_thread.h
	gcc -c -g thread_test.c
common_thread.o: common_thread.c common_thread.h
	gcc -c -g  -pthread common_thread.c
clean:
	rm runner *.o
