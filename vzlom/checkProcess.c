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
#include <time.h>

struct StockThePid {
    pid_t pid;
    char buff[512];
    FILE *pid_pipe;     
} stockthepid;

void Func_StockPid(const char *processtarget) {
    stockthepid.pid_pipe = popen(processtarget, "r");
    fgets(stockthepid.buff, 512, stockthepid.pid_pipe);
    stockthepid.pid = strtoul(stockthepid.buff, NULL, 10);
    FILE *fptr; 
    fptr = fopen("/home/nokkudimu/repos/tekken8_data_collector/temporaryFiles/processIsLaunched.json", "w");
    if (stockthepid.pid == 0) {
        // process is not launched
        fprintf(fptr, "{\n\"processIsLaunched\": false\n}");
        pclose(stockthepid.pid_pipe);
    } else {
        // process is launched
        fprintf(fptr, "{\n\"processIsLaunched\": true\n}");
        pclose(stockthepid.pid_pipe);
    } 
    fclose(fptr);    
    exit(0);  
}

int main() {
    #if defined(COMMAND)
    Func_StockPid(COMMAND);
  #else
    exit(-1);
  #endif
}