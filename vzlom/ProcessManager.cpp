#include "ProcessManager.h"

long ProcessManager::FindBaseAddress(const char *module) {
    int fd = 0;
    char FileLocation[1024];
    char BaseAddress[1024];
    char *ptr = NULL;

    sprintf(FileLocation, "/proc/%lu/maps", ProcessID);

    if((fd = open(FileLocation, O_RDONLY)) < 0) {
        fprintf(stderr, "FAiled to open file!\n");
        exit(EXIT_FAILURE);
    }    

    char *FileBuffer = (char *)malloc(100000);
    if(FileBuffer == NULL) {
        fprintf(stderr, "FAiled malloc()\n");
        exit(EXIT_FAILURE);
    }

    memset(FileBuffer, 0 , 100000);
    memset(BaseAddress, 0 , 1024);

    for(int i = 0; read(fd, FileBuffer + i, 1) > 0; i++);

    close(fd);

    if(module != NULL) {
        if((ptr = strstr(FileBuffer, module)) == NULL) {
            fprintf(stderr, "Failed to find module!\n");
            exit(EXIT_FAILURE);
        }
    } else {
        if((ptr = strstr(FileBuffer, "r-xp")) == NULL) {
            fprintf(stderr, "Failed to find memory module!\n");
            exit(EXIT_FAILURE);
        }
    }

    while(*ptr != '\n' && ptr >= FileBuffer) {
        ptr--;
    }
    ptr++;

    for(int i = 0; *ptr != '-'; i++) {
        BaseAddress[i] = *ptr;
        ptr++;
    }

    free(FileBuffer);

    return strtol(BaseAddress, NULL, 16);

}

bool ProcessManager::WriteProcessMemory(unsigned long address, void *buffer, uint size) {
    lseek(ProcessHandle, address, SEEK_SET);

    if(!write(ProcessHandle, buffer, size)) {
        fprintf(stderr, "Failed to write target memory!\n");
        return false;
    }

    lseek(ProcessHandle, 0, SEEK_SET);
    
    return true;
}

bool ProcessManager::ReadProcessMemory(unsigned long address, void *buffer, uint size) {
    lseek(ProcessHandle, address, SEEK_SET);

    if(!read(ProcessHandle, buffer, size)) {
        fprintf(stderr, "Failed to read target memory!\n");
        return false;
    }

    lseek(ProcessHandle, 0, SEEK_SET);
    
    return true;
}

bool ProcessManager::SignaturePayload(const char *signature, char *payload, const int siglength, const int paylength, const int bsize, uint sigoffset) {
    char *buf = (char *)malloc(siglength * bsize);
    if (buf == NULL) {
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; ReadProcessMemory(TargetBaseAddress + i, buf, siglength * bsize); i += (siglength * bsize)) {
        for (int j = 0; j < ((siglength * bsize) - (siglength - 1)); j++) {
            if(memcmp(buf + j, signature, siglength) == 0) {
                printf("Signature found!\n");

                if(payload != NULL) {
                    WriteProcessMemory((TargetBaseAddress + i + j) + sigoffset, payload, paylength);
                }

                goto END;
            }
        }
    }

    END:

    free(buf);

    return true;
}

ProcessManager::ProcessManager(const char *ProcessName, const char *module) {
    if(strlen(ProcessName) > 1023) {
        fprintf(stderr, "Process name is too long\n");
        exit(EXIT_FAILURE);
    }

    strcpy(ProcessNameStr, ProcessName);

    struct dirent *DirectoryObject = NULL;
    DIR *DirectoryHandle = NULL;

    if((DirectoryHandle = opendir("/proc/")) == NULL) {
        fprintf(stderr, "Failed to attach to /proc/\n");
        exit(EXIT_FAILURE);
    }

    while((DirectoryObject = readdir(DirectoryHandle)) != NULL) {
        if(atoi(DirectoryObject->d_name) != 0) {
            char FilePath[1024];
            char *FileBuffer = NULL;
            __off_t FIleLength = 128;
            int fd = 0;

            sprintf(FilePath, "/proc/%s/status", DirectoryObject->d_name);

            if((fd = open(FilePath, O_RDONLY)) < 0) {
                fprintf(stderr, "Failed to open file!\n");
                exit(EXIT_FAILURE);
            }

            if((FileBuffer = (char *)malloc(FIleLength)) == NULL) {
                fprintf(stderr, "Failed malloc()\n");
                exit(EXIT_FAILURE);
            }
            memset(FileBuffer, 0, FIleLength);

            if(read(fd, FileBuffer, FIleLength) < 0) {
                fprintf(stderr, "Failed to read file contents!\n");
                exit(EXIT_FAILURE);
            }

            close(fd);

            if(strstr(FileBuffer, ProcessNameStr) != NULL) {
                printf("Process found! \n");

                ProcessID = atol(DirectoryObject->d_name);

                char TargetMemoryLocation[1024];
                sprintf(TargetMemoryLocation, "/proc/%s/mem", DirectoryObject->d_name);

                // Get the program base address
                TargetBaseAddress = FindBaseAddress(module);

                if((ProcessHandle =open(TargetMemoryLocation, O_RDWR)) < 0) {
                    fprintf(stderr, "Failed to open target memory!]n");
                    exit(EXIT_FAILURE);
                }

                free(FileBuffer);
                break;
            }

            free(FileBuffer);
        }
    }

    closedir(DirectoryHandle);

}

ProcessManager::~ProcessManager() {
    if(ProcessHandle != 0) {
        close(ProcessHandle);
    }
}