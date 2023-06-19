#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
int main() {
	// 创建一个子进程
	pid_t pid;
	pid = fork();
	if(pid < 0) {
		perror("fork");
		return 0;
	} else if(pid > 0){
		exit(0); // 父进程退出
	}
	
	printf("I am a deamon!\n");
	// 子进程创建新会话
	printf("sid = %d, pid = %d, pgid = %d\n", getsid(getpid()), getpid(), getpgid(getpid()));
	if(setsid() < 0) {
		perror("setsid");
		exit(0);
	}
	printf("after sid = %d, pid = %d, pgid = %d\n", getsid(getpid()), getpid(), getpgid(getpid()));

	// 改变工作目录
	chdir("/");
	
	// 设置文件权限掩码
	if(umask(0) < 0) {
		perror("unmask");
		exit(0);
	}
	
	// 关闭当前文件描述符
	close(0);
	close(1);
	close(2);

	printf("after close!!\n");
	
	sleep(100);
}
