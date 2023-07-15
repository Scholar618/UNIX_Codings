/*创建一个父进程到子进程的管道，并且父进程经由该管道向子进程传送数据*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 20

int main() {
	int fd[2];
	char buf[MAXLINE];
	pid_t pid;
	int n;
	if(pipe(fd) < 0) {
		perror("pipe");
		return 0;
	}
	if((pid = fork()) < 0) {
		perror("fork");
		return 0;
	} else if (pid == 0) { // 子进程
		close(fd[1]); // 关闭写端
		n = read(fd[0], buf, MAXLINE);
		write(STDOUT_FILENO, buf, n); // 输出到终端
	} else { // 父进程
		close(fd[0]); // 关闭读端
		strcpy(buf, "hello world!!\n");
		// write(fd[1], "hello world!!\n", 15);
		write(fd[1], buf, strlen(buf));
	}
	return 0;
}
