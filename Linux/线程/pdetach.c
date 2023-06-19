#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg) {
	pthread_detach(pthread_self()); // 另一种方式
	printf("This is child thread!\n");
	sleep(1);
	pthread_exit("Thread return!");
}

int main() {
	pthread_t tid[5];
	void *retv;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	// 先创建，再回收
	for(int i = 0; i < 5; i++) {
	    pthread_create(&tid[i], &attr, func, NULL);	
	//	pthread_detach(tid); // detach实现线程回收
	}
	while(1) {
	    sleep(1);	
	}
}
