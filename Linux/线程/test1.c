#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *testThread(void *arg) {
	printf("This is the thread test, tid = %lu\n", pthread_self());
	// return NULL;
	printf("input arg = %d\n", *(int*)arg);
	pthread_exit(NULL);
	printf("after pthread exit!\n");
}

int main() {
	pthread_t tid;
	int rel;
	int arg = 5;
	rel = pthread_create(&tid, NULL, testThread, (void*)&arg);
	printf("This is the main thread, tid = %lu\n", tid);
	sleep(1);
	return 0;
}


