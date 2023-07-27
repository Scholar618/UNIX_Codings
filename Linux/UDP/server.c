#include "net.h"

int main(void) 
{
	int fd = -1;
	struct sockaddr_in sin;

	// 1. 创建socket fd (SOCK_DGRAM  UDP程序)
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	// 2. 允许绑定地址快速重用
	int b_reuse = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));

	// 3. 绑定
	// 3.1 填充struct sockaddr_in 结构体变量
	bzero(&sin, sizeof(sin)); // 清空内容
	sin.sin_family = AF_INET; // ipv4
	sin.sin_port = htons(SERV_PORT); // 网络字节序端口号
	// 3.2 让服务器程序能绑定在任意的IP上
#if 1
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
#else
	if(inet_pton(AF_INET, SERV_IP_ADDR, (void *)&sin.sin_addr) != 1) {
		perror("inet_pton");
		exit(1);
	}
#endif
	// 3.3 绑定
	if(bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("bind");
		exit(1);
	}
	printf("Serve starting ......OK!\n");	
	char buf[BUFSIZ];
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);
	while(1) {
		bzero(buf, BUFSIZ);
		if(recvfrom(fd, buf, BUFSIZ-1, 0, (struct sockaddr *)&cin, &addrlen) <0 ) {
			perror("recvfrom");
			continue;
		}
		char ipv4_addr[16];
		if(!inet_ntop(AF_INET, (void *)&cin.sin_addr, ipv4_addr, sizeof(cin))) {
			perror("inet_ntop");
			exit(1);
		}
		printf("Receive from (%s:%d), data:%s", ipv4_addr, ntohs(sin.sin_port), buf);
		
		if(!strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) { // 用户输入quit退出客户端
			printf("Client(%s:%d) is exiting!\n",ipv4_addr, ntohs(sin.sin_port));
		}
	}
	close(fd);
	return 0;
}

