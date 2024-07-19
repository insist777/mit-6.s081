#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char* argv[]){
    int p1[2];
    int p2[2];
    char buf[] ={'b'};
    int len = sizeof(buf);
    pipe(p1);
    pipe(p2);
    if (fork() == 0){
        close(p1[1]);
        close(p2[0]);
        if (read(p1[0], buf, len) != len){
            printf("child read error\n");
            exit(1);
        }
        printf("%d: received ping\n", getpid());
        if (write(p2[1], buf, len) != len){
            printf("child write error\n");
            exit(1);
        }
        exit(0);
    }else{
        close(p1[0]);
        close(p2[1]);
        if (write(p1[1], buf, len) != len){
            printf("master write error\n");
            exit(1);
        }
        if (read(p2[0], buf, len) != len){
            printf("master read error\n");
            exit(1);
        } 
        printf("%d: received pong\n", getpid());
        exit(0);   
    }
    exit(0);
}