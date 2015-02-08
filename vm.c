#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

vm * createVM(size_t numRegisters, size_t memorySize) {
  vm *vm = malloc(sizeof *vm);
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
  byte *start = code;
  while(opcode = *(code++)) {
    printInfo(vm);
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

    INSTRUCTION_START(04) // i8sub dest reg1 reg2
      byte dest = *(code++);
      byte x    = *(code++);
      byte y    = *(code++);
      printf("i8sub\t!!%02X\t!!%02X\t!!%02X\n", dest, x, y);
      vm->registers[dest] = vm->registers[x] - vm->registers[y];
    INSTRUCTION_END

    INSTRUCTION_START(05) // jmp dest
      byte dest = *(code++);
      printf("jmp\t?%02X\n", dest);
      code = start + dest;
    INSTRUCTION_END

    INSTRUCTION_START(06) // jeq dest reg1 reg2
      byte dest = *(code++);
      byte x    = vm->registers[*(code++)];
      byte y    = vm->registers[*(code++)];
      printf("jeq\t?%02X\t!!%02X\t!!%02X\n", dest, x, y);
      if(x == y) code = start + dest;
    INSTRUCTION_END

    INSTRUCTION_START(07) // jne dest reg1 reg2
      byte dest = *(code++);
      byte x    = vm->registers[*(code++)];
      byte y    = vm->registers[*(code++)];
      printf("jne\t?%02X\t!!%02X\t!!%02X\n", dest, x, y);
      if(x != y) code = start + dest;
    INSTRUCTION_END

    INSTRUCTION_START(08) // jlt dest reg1 reg2
      byte dest = *(code++);
      byte x    = vm->registers[*(code++)];
      byte y    = vm->registers[*(code++)];
      printf("jlt\t?%02X\t!!%02X\t!!%02X\n", dest, x, y);
      if(x < y) code = start + dest;
    INSTRUCTION_END

    INSTRUCTION_START(09) // jgt dest reg1 reg2
      byte dest = *(code++);
      byte x    = vm->registers[*(code++)];
      byte y    = vm->registers[*(code++)];
      printf("jgt\t?%02X\t!!%02X\t!!%02X\n", dest, x, y);
      if(x > y) code = start + dest;
    INSTRUCTION_END

    INSTRUCTION_START(0A) // jle dest reg1 reg2
      byte dest = *(code++);
      byte x    = vm->registers[*(code++)];
      byte y    = vm->registers[*(code++)];
      printf("jle\t?%02X\t!!%02X\t!!%02X\n", dest, x, y);
      if(x <= y) code = start + dest;
    INSTRUCTION_END

    INSTRUCTION_START(0B) // jge dest reg1 reg2
      byte dest = *(code++);
      byte x    = vm->registers[*(code++)];
      byte y    = vm->registers[*(code++)];
      printf("jge\t?%02X\t!!%02X\t!!%02X\n", dest, x, y);
      if(x >= y) code = start + dest;
    INSTRUCTION_END

    default:
      fprintf(stderr, "Unknown opcode %X encountered. Treated as nop.\n", opcode);
    }
  }
}

void printInfo(vm *vm) {
    for(size_t i = 0; i < vm->numRegisters; ++i) {
        printf("%d ", vm->registers[i]);
    }
    printf("\n");
}
