#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

typedef unsigned int unit;
class ProcessManager {
    private: 
        char ProcessNameStr[1024];
        long ProcessID = 0;
        int ProcessHandle = 0;

        long FindBaseAddress(const char *module = NULL);

    public:
        unsigned long TargetBaseAddress = 0;

        ProcessManager(const char *ProcessName, const char *module = NULL);
        ~ProcessManager();

        bool SignaturePayload(const char *signature, char *payload, const int siglength, const int paylength, const int bsize, uint sigoffset = 0);

        bool WriteProcessMemory(unsigned long address, void *buffer, uint size);
        bool ReadProcessMemory(unsigned long address, void *buffer, uint size);

};