#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

struct StockThePid {
    pid_t pid;
    char buff[512];
    FILE *pid_pipe;    
} stockthepid;

void Func_StockPid(const char *processtarget) {
    stockthepid.pid_pipe = popen(processtarget, "r");
    fgets(stockthepid.buff, 512, stockthepid.pid_pipe);
    stockthepid.pid = strtoul(stockthepid.buff, NULL, 10);

    if (stockthepid.pid == 0) {
        printf("Process is not launched!\n");
        pclose(stockthepid.pid_pipe);
        exit(-1);
    } else {
        printf("Process found - PID NUMBER -> {%d} \n", stockthepid.pid);
        pclose(stockthepid.pid_pipe);
    }   
}

void ReadProcessMemory(unsigned long address, unsigned int pid) {
    int buf = 0; 
    int err_code = ptrace(PTRACE_ATTACH, stockthepid.pid, NULL, NULL);

    if (err_code == -1) {
        printf("ERROR 1\n");
        exit(-1);
    }

    printf("Reading the address of the process... \n");
    for (int i = 0; i < 1; i++) {
        buf = ptrace(PTRACE_PEEKDATA, stockthepid.pid, address + i * sizeof(int), NULL);

        if (err_code == -1) {
            printf("ERROR 2\n");
            exit(-1);
        }
        printf("%d\n", buf);
    }



    err_code = ptrace(PTRACE_DETACH, stockthepid.pid, NULL, NULL);
    if (err_code == -1) {
        printf("ERROR 3\n");
        exit(-1);
    }
}

//void WriteProcessMemory(unsigned long address, unsigned int pid) {
//    int WhatValue = 0;
//    int buf = 0;
//
//    printf("Enter a new value!\n");
//    scanf("%d", &WhatValue);
//
//    int err_code = ptrace(PTRACE_ATTACH, stockthepid.pid, NULL, NULL);
//    if (err_code = -1) {
//        printf("ERROR 1\n");
//        exit(-1);
//    }
//    wait(NULL);
//    printf("Rewriting the value!\n");
//    for (int i = 0; i < 1; i++) {
//        buf = ptrace(PTRACE_POKEDATA, stockthepid.pid, address + i * sizeof(int), WhatValue);
//        if (buf == -1) {
//            printf("ERROR 2]\n");
//            exit(-1);
//        }
//        printf("Value rewritten!\n");
//    }
//    err_code = ptrace(PTRACE_DETACH, stockthepid.pid, NULL, NULL);
//    if (err_code == -1) {
//        printf("ERROR 3\n");
//        exit(-1);
//    }
//}

int main() {
    Func_StockPid("pidof -s GameThread"); // don't know the process name
    ReadProcessMemory(0x6ffffc65af3c, stockthepid.pid);
    //WriteProcessMemory(0x6ffffc65af3c, stockthepid.pid);
 
    return 0;
}