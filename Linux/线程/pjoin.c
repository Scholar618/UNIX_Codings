#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg) {
	printf("This is child thread!\n");
	sleep(1);
	pthread_exit("Thread return!");
}

int main() {
	pthread_t tid[5];
	void *retv;
	// 先创建，再回收
	for(int i = 0; i < 5; i++) {
	    pthread_create(&tid[i], NULL, func, NULL);	
	}
	// 回收五个线程
	for(int i = 0; i < 5; i++) {
	    pthread_join(tid[i], &retv);
	    printf("Thread ret = %s\n",(char*)retv);
	}

	sleep(1);
}
