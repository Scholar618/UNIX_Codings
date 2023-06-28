/*
 *	判断机器字节序
 * */
#include <stdio.h>

void buteorder() {
	union {
		short value;
		char union_byte[sizeof(short)];
	} test;
	test.value = 0x0102;
	if((test.union_byte[0] == 1) && (test.union_byte[1] == 2)) {
		printf("big endian!\n");
	} else if((test.union_byte[0] == 2) && (test.union_byte[1] == 1)) {
		printf("little endian!\n");
	} else {
		printf("error!\n");
	}
}

int main() {
	buteorder();
}

