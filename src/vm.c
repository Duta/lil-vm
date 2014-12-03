#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

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
        switch(opcode) {
        case 0x01: { // i8load register value
            byte reg = *(code++);
            byte val = *(code++);
            printf("i8load !!%d ?%02X\n", reg, val);
            vm->registers[reg] = val;
            } break;
        }
    }
}
