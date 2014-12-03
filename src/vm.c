#include <stdlib.h>
#include "vm.h"

insexec instructions[] = {
    // TODO
};

vm * createVM(int numRegisters, int memorySize) {
    vm *vm = malloc(sizeof(vm));
    vm->numRegisters = numRegisters;
    vm->memorySize   = memorySize;
    vm->registers    = calloc(numRegisters, sizeof(byte));
    vm->memory       = calloc(memorySize,   sizeof(byte));
    return vm;
}

void destroyVM(vm *vm) {
    free(vm->registers);
    free(vm->memory);
    free(vm);
}

void exec(vm *vm, byte *code) {
    byte opcode;
    while(opcode = *(code++)) {
        code = instructions[opcode](vm, code);
    }
}
