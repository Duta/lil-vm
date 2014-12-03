#ifndef VM_H
#define VM_H

#include <stdint.h>

typedef uint8_t byte;

typedef struct {
    int numRegisters;
    int memorySize;
    byte *registers;
    byte *memory;
} vm;

typedef byte *(*insexec)(vm *vm, byte *code);

extern insexec instructions[];

vm * createVM(int numRegisters, int memorySize);
void destroyVM(vm *vm);

void exec(vm *vm, byte *code);

#endif
