#includ "net.h"	
int main(void) {
	int fd = -1;
	struct sockaddr_in sin;
   // 创建socked fd	
	if( (fd = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
		perror("socket");
		exit(1);
	}
	
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
	
	// 绑定开始
	if(bind(fd, (struct sockaddr *) &sin, sizeof(sin))<0) {
		perror("bind!!");
		exit(1);
	}

	// 调用listen()把主动套接字变成被动套接字
	if( listen(fd, BACKLOG) < 0 ) {
		perror("listen");
		exit(1);
	}	
	int newfd = -1;
	// 阻塞等待客户端连接请求
	newfd = accept(fd, NULL, NULL);
	if(newfd < 0) {
		perror("accept");
		exit(1);
	}
	// 读写操作
	int ret = -1;
	char buf[BUFSIZ];
	while(1) {
			
		bzero(buf, BUFSIZ);
		do {		
			ret = read(newfd, buf, BUFSIZ-1);
		} while (ret < 0 && EINTR == errno);
		if (ret < 0) {
			perror("read");
			exit(1);
		}
		if(!ret) {
			break;
		}
		printf("Receive data:%s\n", buf);
		if(strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) {
			printf("Client is exiting!\n");
			break;
		}
	}	
	close(newfd);
	close(fd);
	return 0;
}
