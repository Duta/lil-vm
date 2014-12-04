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

#define INSTRUCTION_START(opcode) case 0x##opcode: {
#define INSTRUCTION_END } break;

        INSTRUCTION_START(01) // i8load register value
            byte reg = *(code++);
            byte val = *(code++);
            printf("i8load\t!!%02X\t?%02X\n", reg, val);
            vm->registers[reg] = val;
        INSTRUCTION_END

        INSTRUCTION_START(02) // i8mov dest source
            byte dest = *(code++);
            byte src  = *(code++);
            printf("i8mov\t!!%02X\t!!%02X\n", dest, src);
            vm->registers[dest] = vm->registers[src];
        INSTRUCTION_END

        INSTRUCTION_START(03) // i8add dest reg1 reg2
            byte dest = *(code++);
            byte x    = *(code++);
            byte y    = *(code++);
            printf("i8add\t!!%02X\t!!%02X\t!!%02X\n", dest, x, y);
            vm->registers[dest] = vm->registers[x] + vm->registers[y];
        INSTRUCTION_END

        }
    }
}
