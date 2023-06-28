#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
	int re;
	int fd;
	char buf[32];
	re = mkfifo("/myfifo", 0666);
	if(re < 0) {
		perror("mkfifo");
//		return 0;
	}
	fd = open("/myfifo", O_WRONLY|O_NONBLOCK);
	if(fd < 0) {
		perror("open");
		return 0;
	}
	printf("after open!\n");
	while(1) {
		fgets(buf, 32, stdin);
		write(fd, buf, strlen(buf));
	}

}
