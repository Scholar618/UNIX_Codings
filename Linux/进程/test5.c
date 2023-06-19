#include <stdio.h>
#include <unistd.h>

int main() {
	
	//if(execl("/bin/ls", "ls", "-a", "-l", "./", NULL) < 0) {
	//	perror("execl");
	//}
	pid_t pid;
	printf("Before:\n");
	pid = fork();

	if(pid == 0) {
	    if(execlp("ls", "ls", "-a", "-l", "./", NULL) < 0) {
    	  perror("execlp");
	    }
	} 
	printf("After:\n");
}
