#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

// 端口号和IP地址
#define PORT 8000
#define IP "192.168.0.108"

int main(int argc, char* argv[]) 
{
	int sockfd; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("socket");
		return -1;
	}

	// 设置服务器地址结构体
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;   // IPV4
	server_addr.sin_port = htons(PORT); // 端口号
	if(inet_pton(AF_INET, IP, &server_addr.sin_addr.s_addr) != 1) {
		perror("inet_pton");

		return -1;
	}
	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0 ) {
		perror("connect");
		close(sockfd);
		return -1;
	}
	char send_buf[512] = {0};
	printf("send data to %s:%d\n",IP ,PORT);
	while(1)
	{
		printf("send:");
		fgets(send_buf,sizeof(send_buf),stdin); // 输入内容
		send_buf[strlen(send_buf)-1]='\0';
		send(sockfd, send_buf, strlen(send_buf), 0);   // 向服务器发送信息
	}

	close(sockfd);

	return 0;

}
