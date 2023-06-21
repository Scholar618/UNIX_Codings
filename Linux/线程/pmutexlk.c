// 互斥锁的使用

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
FILE *fp;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *func2(void *arg) {
	pthread_detach(pthread_self());
	printf("This is func2 thread!\n");
	char str[] = "I write fun2 thread!\n";
	char c;
	int i = 0;
	while(1) {
			pthread_mutex_lock(&mutex);
			while(i < strlen(str)) {
				c = str[i];
				i++;
				fputc(c, fp);
				usleep(1);
			}
			pthread_mutex_unlock(&mutex);
			i = 0;
			usleep(1);
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
			pthread_mutex_lock(&mutex);
			while(i < strlen(str)) {
				c = str[i];
				i++;
				fputc(c, fp);
				usleep(1);
			}
			pthread_mutex_unlock(&mutex);
			i = 0;
			usleep(1);
	}
	pthread_exit("fun1 return!!");

}

int main() {
	pthread_t tid;
	void *retv;
	int i;
	fp = fopen("1.txt", "a+");
	if(fp == NULL) {
		perror("fopen");
		return 0;
	}
	pthread_create(&tid, NULL, func1, NULL);
	pthread_create(&tid, NULL, func2, NULL);
	while(1) {
			sleep(1);
	}
}
