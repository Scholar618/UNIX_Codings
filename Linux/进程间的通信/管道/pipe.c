#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main() {
	int pfd[2];
	int re;
	char buf[20];
	pid_t pid;
	re = pipe(pfd);
	if(re < 0) {
		perror("pipe");
		return 0;
	}
	pid = fork();
	if(pid < 0) {
		perror("fork");
		return 0;
	} else if(pid == 0) { // 子进程
		while(1) {
			strcpy(buf, "I love Linux!");
			write(pfd[1], buf, strlen(buf));
			sleep(1);
		}
	} else { // 父进程	
		while(1) {
			re = read(pfd[0], buf, 20);
			if(re > 0) {
				printf("read pipe = %s\n", buf);
			}
		}
	}
	return 0;
}
