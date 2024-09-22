#include "ProcessManager.h"

int main() {
    const char Signature[] = "\x48\x8b\x45\x28\x83\x28\x01\x48";
    char OpCode[] = "\x90\x90\x90";

    ProcessManager procManager("TEKKEN 8.exe");

    procManager.SignaturePayload(Signature, OpCode, strlen(Signature), strlen(OpCode), 64, 4);

    exit(EXIT_SUCCESS);
}