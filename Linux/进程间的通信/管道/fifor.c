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
	fd = open("/myfifo", O_RDONLY);
	if(fd < 0) {
		perror("open");
		return 0;
	}
	while(1) {
		re = read(fd, buf, 32);
		if(re > 0) {
			printf("read fifo = %s",buf);
		} else if(re == 0) {
			exit(0);
		}
	}
}
