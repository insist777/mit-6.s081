#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

__attribute__((noreturn)) 
void primes(int p1[2]){
    close(p1[1]);
    int top;
    int data;
    if (read(p1[0], &top, sizeof(int)) == sizeof(int)){
        printf("prime %d\n", top);
        int p2[2];
        pipe(p2);
        while (read(p1[0], &data, sizeof(int)) == sizeof(int)){
            if (data % top){
                write(p2[1], &data, sizeof(int));
            }
        }
        close(p2[1]);
        if (fork() == 0){
            primes(p2);
        }else{
            close(p2[0]);
            wait(0);
        }
    }
    exit(0);
}

int main(int argc,char* argv[]){
    int p1[2];
    pipe(p1);
    for (int i = 2; i <= 35; i++){
        write(p1[1], &i, sizeof(int));
    }

    if (fork() == 0){
        primes(p1);
    }
    close(p1[0]);
    close(p1[1]);
    wait(0);
    exit(0);
    
    
}