#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	pid_t pid;
	pid_t rpid;
	pid = fork();
	int status;
	if(pid < 0) {
		perror("fork");
		return 0;
	} else if(pid == 0) {
		sleep(1);
		printf("child will exit!\n");
		exit(1);
	} else if(pid > 0) {
		rpid = wait(&status);
		printf("Get child status = %x\n", WEXITSTATUS(status));		
	}
	// 判断进程中是否有僵尸
	while(1) {
		sleep(1);
	}
	return 0;
}
