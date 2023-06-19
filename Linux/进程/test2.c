#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t pid;
	printf("before fork pid = %d\n", (int)pid);
	pid = fork();

	if(pid > 0) { // 父进程
		printf("This is father process\n");
		while(1) {
			sleep(1);
			printf("father sleep!\n");
		}
	} else if(pid == 0) { // 子进程
		printf("This is child process\n");
		while (1)
		{
			sleep(1);
			printf("child sleep\n");
		}
		
	} else { // 出错了
		perror("fork");
		return 0;
	}
						
	printf("pid = %d\n", (int)pid);
	return 0;
}
