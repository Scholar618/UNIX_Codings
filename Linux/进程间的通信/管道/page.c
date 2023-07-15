/*每次一页的显示已产生的数据*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAXLINE 20
#define DEF_PAGER "/bin/more"

int main(int argc, char* argv[]) {
	int n, fd[2];
	pid_t pid;
	char *pager, *argv0;
	char buf[MAXLINE];
	FILE *fp;
	// 检查程序运行时传入的参数个数
	if(argc != 2) {
		printf("Usage:a.out <pathname>\n");
		return 0;
	}
	// 打开文件并将其读入内存
	if((fp = fopen(argv[1], "r")) == NULL) {
		perror("argv");
	}
	// 创建管道
	if(pipe(fd) < 0) {
		perror("pipe");
	} 
	// 创建子进程
	if((pid = fork()) < 0) {
		perror("fork");
	} else if(pid > 0) { // 父进程
		close(fd[0]); // 关闭读端
		// 从文件中读取一行数据，然后将数据写入管道的写入端。
		while(fgets(buf, MAXLINE, fp) != NULL) {
			n = strlen(buf);
			if(write(fd[1], buf, n) != n) {
				perror("write to pipe");
				return 0;
			}
		}
		// 检查文件读写是否出错
		if(ferror(fp)) {
			perror("fgets");
			return 0;
		}
		close(fd[1]); // 关闭写端
		if(waitpid(pid, NULL, 0) < 0) {
			perror(waitpid);
		}
		exit(0);
	} else {
		close(fd[1]);
		if(fd[0] != STDIN_FILENO) {
			if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
				perror(dup2);
				return 0;
			}
			close(fd[0]);
		}
		if((pager = getenv("PAGER")) == NULL) {
			pager = DEF_PAGER;
		}
		// 在一个字符串中查找某个字符最后一次出现的位置
		if((argv0 = strrchr(pager, "/")) != NULL) {
			argv0++;
		} else {
			argv0 = pager;
		}

		if(execl(pager, argv0, (char *)0) < 0) {
			perror("execl");
			return 0;
		}
	}

	return 0;


}
