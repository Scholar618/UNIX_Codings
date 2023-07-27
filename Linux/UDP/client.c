#include "net.h"

/*UDP usage:
 * ./client serv_ip serv_port*/

void usage(char *s) {
	printf("\nThis is udp usage!\n");
	printf("\nUsage:\n\t %s serv_ip serv_port", s);
	printf("\n\t serv_ip: udp server ip address");
	printf("\n\t serv_port: udp server port(serv_port > 5000)\n\n");
}

int main(int argc, char* argv[]) {
	int fd = -1;
	int port = SERV_PORT;
	port = atoi(argv[2]);
	if(port <= 5000) {
		usage(argv[0]);
		exit(1);
	}
    struct sockaddr_in sin;
	if(argc != 3) {
		usage(argv[0]);
		exit(1);
	}

    // 1. 创建socket fd (SOCK_DGRAM  UDP程序)
    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

	// 3.1 填充struct sockaddr_in 结构体变量
    bzero(&sin, sizeof(sin)); // 清空内容
    sin.sin_family = AF_INET; // ipv4
    sin.sin_port = htons(SERV_PORT); // 网络字节序端口号
    // 3.2 让服务器程序能绑定在任意的IP上
#if 0
    sin.sin_addr.s_addr = inet_addr(argv[1]);
#else
    if(inet_pton(AF_INET, argv[1], (void *)&sin.sin_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }
#endif
	printf("Client starting ......OK!\n");
	char buf[BUFSIZ];
	while(1) {
		printf("Please input : ");
		bzero(buf, BUFSIZ);
		if(fgets(buf, BUFSIZ-1, stdin) == NULL) {
			perror("gets");
			continue;
		}
		sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&sin, sizeof(sin));
		if(!strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) { // 用户输入quit退出
            printf("Client is exiting!\n");
			break;
        }
	}
	close(fd); 

	return 0;
}
