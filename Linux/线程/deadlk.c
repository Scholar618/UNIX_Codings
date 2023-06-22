// 互斥锁的使用

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
FILE *fp;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *func2(void *arg) {
	pthread_detach(pthread_self());
	printf("This is func2 thread!\n");
	char str[] = "I write fun2 thread!\n";
	char c;
	int i = 0;
	while(1) {
			pthread_mutex_lock(&mutex2);
			printf("%d,I got lock2\n",(int)arg);
			sleep(1);
			pthread_mutex_lock(&mutex1);
			printf("%d,I got 2 locks\n",(int)arg);

			pthread_mutex_unlock(&mutex1);
			pthread_mutex_unlock(&mutex2);
			sleep(10);
	}
	pthread_exit("fun2 return!!");
}


void *func1(void *arg) {
	pthread_detach(pthread_self());
	printf("This is func1 thread!\n");
	char str[] = "You read fun1 Line!\n";
	char c;
	int i = 0;
	while(1) {
			pthread_mutex_lock(&mutex1);
			printf("%d,I got lock1\n", (int)arg);
			sleep(1);
			pthread_mutex_lock(&mutex2);
			printf("%d,I got 2 locks\n",(int) arg);

			pthread_mutex_unlock(&mutex2);
			pthread_mutex_unlock(&mutex1);
			sleep(10);
	}
	pthread_exit("fun1 return!!");

}

int main() {
	pthread_t tid1, tid2;
	void *retv;
	int i;
	fp = fopen("1.txt", "a+");
	if(fp == NULL) {
		perror("fopen");
		return 0;
	}
	pthread_create(&tid1, NULL, func1, 1);
	sleep(5);
	pthread_create(&tid2, NULL, func2, 2);
	while(1) {
			sleep(1);
	}
}
