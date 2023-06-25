#include "net.h"
int main() {
	int fd = -1;
	struct sockaddr_in sin;
    // 创建socked fd
    if( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
	
	// 连接服务器
	// 填充
	// 绑定
    // 填充struct sockaddr_in 结构体变量
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERV_PORT); //网络字节序端口号
#if 0
    sin.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);
#else
    if(inet_pton(AF_INET, SERV_IP_ADDR, (void*)&sin.sin_addr)!=1) {
        perror("inet_pton");
        exit(1);
    }
#endif
    if(connect(fd, (struct sockaddr*)&sin, sizeof(sin))<0) {
		perror("connect");
		exit(1);
	}
	
	// 读写数据
	char buf[BUFSIZ];
	while(1) {
		bzero(buf, BUFSIZ);
		if(fgets(buf, BUFSIZ-1, stdin) == NULL) {
			continue;
		}
		write(fd, buf, strlen(buf));

		if(!strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) {
			printf("Client is exiting!\n");
			break;
		}
	}

	// 关闭套接字
	close(fd);
	return 0;
}
