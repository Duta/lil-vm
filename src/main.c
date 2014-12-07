#include <stdio.h>
#include "vm.h"

byte sampleProgram[] = {
    /*
    // TODO
    0x01, 0x03, 0xED, // i8load !!3 ?ED
    0x01, 0x01, 0xAA, // i8load !!1 ?AA
    0x02, 0x00, 0x03, // i8mov !!0 !!3
    0x01, 0x04, 0x07, // i8load !!4 ?07
    0x03, 0x07, 0x03, 0x04, // i8add !!7 !!3 !!4
    0x00              // halt
    */
    0x01, 0x00, 0x00,       // i8load !!0 ?00
    0x01, 0x01, 0x03,       // i8load !!1 ?03
    0x01, 0x02, 0xFF,       // i8load !!2 ?FF
    0x03, 0x00, 0x00, 0x01, // i8add !!0 !!0 !!1
    0x07, 0x09, 0x00, 0x02, // ifn ?9 !!0 !!2
    0x00                    // halt
};

int main(int argc, char **argv) {
    // Create a machine with 8 registers and 1kb of memory
    vm *vm = createVM(8, 1024);

    // Run a simple program
    exec(vm, sampleProgram);

    // Print the resultant state of the machine's registers
    printInfo(vm);

    // Free the machine's memory and registers
    destroyVM(vm);

    printf("Done\n");
    return 0;
}
