#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

typedef pthread_t pt_t;
typedef unsigned int uint_t;

pt_t main_td;

void print_ids(const char* str)
{
	pid_t pid;	//process
	pt_t tid;	// thread
	
	pid = getpid();
	tid = pthread_self();

	printf("%s pid: %u tid: %u (0x%x)\n", str, (unsigned int)pid, (unsigned int) tid, (unsigned int)tid);
	
}

void func(void *arg)
{
	print_ids("new thread: ");
	return ((void*) 0);
}

int main()
{
	int err = pthread_create(&main_td, NULL, func, NULL);
	if (err != 0) 
	{
		printf("create thread error : %s\n", strerror(err));
		return 1;
	}

	printf("main thread: pid: %u tid: %u (0x%x)\n",
		(uint_t)getpid(), (uint_t)pthread_self(), (uint_t)pthread_self());

	print_ids("main thread:");
	sleep(1);
	
	return 0;
}

