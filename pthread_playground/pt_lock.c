#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

typedef pthread_t pt_t;
typedef unsigned int uint_t;

pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;

void lock_func(void* arg)
{
	pid_t pid;	//process
	pt_t tid;	// thread
	
	pid = getpid();
	tid = pthread_self();

	printf("want to lock mutex, msg=%s, tid=%u\n", (char*)arg, (uint_t)tid);
	
	pthread_mutex_lock( &mt );
	printf("I[tid=%u] am using, (*|^_^|*)\n", (uint_t)tid);
	sleep(10);
	pthread_mutex_unlock( &mt );
}

void try_lock_func(void* arg)
{
	// printf("try to lock mutex, tid=%u\n", (uint_t)pthread_self());
	
	uint_t tid = (uint_t)pthread_self();
	int counter = 0;
	
	while ( pthread_mutex_trylock( &mt ) )
	{
		sleep(1);
		++counter;
		
		printf("after sleep 1s, i [tid=%u] want to try again, iter=%d.\n", tid, counter);
	}
	printf("It is my[tid=%u] turn, so long i waited...msg=%s\n", tid, (char*)arg);
	pthread_mutex_unlock( &mt );	
}

#define XX_CREATE_FAILED(err)	\
	printf("create thread error : %s\n", strerror(err));\
	return 1;	

int main()
{
	int rc;
	pt_t pt1, pt2, pt3;
	
	const char* msg1 = "block";
	const char* msg2 = "unblock";
	
	rc = pthread_create(&pt1, NULL, (void*)&lock_func, (void*)msg1);	if (rc != 0) 
	{
		XX_CREATE_FAILED(rc);
	}
	
	rc = pthread_create(&pt2, NULL, (void*)&lock_func, (void*)msg1);	if (rc != 0)
	{
		XX_CREATE_FAILED(rc);
	}
	sleep(1);
	
	rc = pthread_create(&pt3, NULL, (void*)&try_lock_func, (void*)msg2);	if (rc != 0)
	{
		XX_CREATE_FAILED(rc);
	}
	
	pthread_join(pt1, NULL);
	pthread_join(pt2, NULL);
	pthread_join(pt3, NULL);	
	return 0;
}
