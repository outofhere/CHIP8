#include <stdio.h>
#include <iostream>
#include "chip8.cc"

int main(int argc, const char **argv) {
    chip8 console;
    std::cout << "[*] Starting program" << std::endl;
    console.loadRom("test");
    console.memoryLayout[0] = 'd';
    console.memoryLayout[1] = 'e';
    console.memoryLayout[2] = 'a';
    console.memoryLayout[3] = 'd';
    console.memoryLayout[4] = 'b';
    console.memoryLayout[5] = 'e';
    console.memoryLayout[6] = 'e';
    console.memoryLayout[7] = 'f';
    console.opcodeFetch(&console.memoryLayout[0]);
    return 0;
}
