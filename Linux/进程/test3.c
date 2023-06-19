#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
		
	printf("hello world!\n");
	// 刷新流缓冲区的exit
	exit(0);
	// 不刷新流缓冲区的exit
	_exit(0);
	return 0;
}
