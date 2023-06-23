/*题目：编写一个程序，创建一个子进程，并在子进程中执行一个命令，然后在父进程中等待子进程结束，并输出子进程的退出状态。*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid = fork(); // 创建子进程
	if(pid == 0) { // 子进程
		execl("/bin/ls", "ls", "-l", NULL); //执行ls -l 命令
		perror("execl"); // 若execl函数返回，说明execl发生了错误
		exit(1);
	} else if(pid > 0) { // 父进程
		int status; // 等待的状态
		wait(&status); // 等待子进程结束
		if(WIFEXITED(status)) { // 如果子进程正常终止
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		} else {
			printf("Child process exited abnormally\n");
		}
	} else { // 如果fork失败
		perror("fork");
		exit(1);
	}
	return 0;
}

