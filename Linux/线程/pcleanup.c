#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void cleanup(void *arg) {
	printf("Cleanup, arg = %s\n",(char*)arg);
}

void *func(void *arg) {
	printf("This is child thread!!\n");
	pthread_cleanup_push(cleanup, "abcd");
	while(1) {
		sleep(1);
	}
	pthread_exit("Thread return.");
	pthread_cleanup_pop(0);
}

int main() {
	pthread_t tid;
	void *retv;
	int i;
	pthread_create(&tid, NULL, func, NULL);
	sleep(1);
	pthread_cancel(tid);
	pthread_join(tid, &retv);
	while(1) {
		sleep(1);
	}
}
