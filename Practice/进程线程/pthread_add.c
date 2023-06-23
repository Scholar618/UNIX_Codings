/*题目：假设有一个数组A，长度为N，其中每个元素都是一个整数。
 * 请编写一个程序，创建M个线程，
 * 每个线程计算数组A的一个子数组的和，并把结果累加到一个全局变量S中。
 * 当所有线程结束后，主线程输出S的值。*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define MaxSize 1000
#define M 10

int arr[MaxSize]; //定义数组大小，大小为1000
int s = 0; // 数组总和
pthread_mutex_t mutex; // 互斥锁

void *thread_func(void *arg) {
	int id = *(int *)arg;// 注意参数传递
	int start = id * (MaxSize / M);
	int end = (id == M - 1) ? MaxSize : (id + 1) * (MaxSize / M); // 确定最后一个数
	int sum = 0;
	for(int i = start; i < end; i++) {
		sum += arr[i];
	}
	pthread_mutex_lock(&mutex);
	s+=sum;
	pthread_mutex_unlock(&mutex);
}

int main() {
	// 初始化数组,大小分别是1,2,...,1000
	for(int i = 0; i < MaxSize; i++) {
		arr[i] = i + 1;
	}
	
	// 创建10个线程
	pthread_t thread[M];
	int pid[M];// 线程id
	for(int i = 0; i < M; i++) {
		pid[i] = i;
		if(pthread_create(&thread[i], NULL, thread_func, &pid[i]) != 0) {
			perror("pthread_create");
			exit(1);
		}
	}

	// 等待所有线程结束
	for(int i = 0; i < M; i++) {
		if(pthread_join(thread[i], NULL) != 0) {
			perror("pthread_join");
			exit(0);
		}
	}

	// 最后输出结果
	printf("The sum of array is %d\n", s);

	return 0;

}


