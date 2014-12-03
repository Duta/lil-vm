#include <stdio.h>
#include "vm.h"

byte sampleProgram[] = {
    // TODO
};

int main(int argc, char **argv) {
    // Create a machine with 8 registers and 1kb of memory
    vm *vm = createVM(8, 1024);

    // Run a simple program
    exec(vm, sampleProgram);

    // Free the machine's memory and registers
    destroyVM(vm);

    printf("Done\n");
    return 0;
}
