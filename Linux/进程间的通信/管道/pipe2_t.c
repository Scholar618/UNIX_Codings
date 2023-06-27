#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
    int pfd[2];
    int i;
    int re;
    char buf[40]={0};
    pid_t pid;
    re = pipe(pfd);
    if(re<0){
        perror("pipe");
        return 0;
    }
    printf("%d,%d\n",pfd[0],pfd[1]);
 
    for(i=0;i<2;i++){
        pid = fork();
        if(pid<0){
            perror("fork");
            return 0;
        }else if(pid>0){
 
        }else{
            break;   
             
        }
    }
    if(i==2){
        close(pfd[1]);
        while(1){
            memset(buf,0,40);
            re=read(pfd[0],buf,40);
            if(re>0){
                printf("%s\n",buf);
            }    
        }
        return 0;
    }
 
    if(i==1){
        close(pfd[0]);
        while(1){
            strcpy(buf,"this is 2 process");
            write(pfd[1],buf,strlen(buf));
            usleep(930000);
        }
        return 0;
    }
    if(i==0){
        close(pfd[0]);
        while(1){
            strcpy(buf,"this is 1 process");
            write(pfd[1],buf,strlen(buf));
            sleep(1);
        }
 
        return 0;
    }
 
 
}
