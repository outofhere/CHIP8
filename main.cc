#include <stdio.h>
#include <iostream>
#include "chip8.cc"

int main(int argc, const char **argv) {
    chip8 console;
    std::cout << "[*] Starting program" << std::endl;
    console.loadRom("test");
    console.memoryLayout[0x200] = 0x02;
    console.memoryLayout[0x201] = 0x20;
    console.memoryLayout[0x202] = 0x02;
    console.memoryLayout[0x203] = 0x40;
    console.memoryLayout[0x204] = 0x00;
    console.memoryLayout[0x205] = 0xE0;
    console.memoryLayout[0x206] = 0x00;
    console.memoryLayout[0x207] = 0xE0;

    console.memoryLayout[0x220] = 0x00;
    console.memoryLayout[0x221] = 0xEE;
    console.memoryLayout[0x240] = 0x00;
    console.memoryLayout[0x241] = 0xEE;

    for (uint8_t i; i < 6; ++i) {
        console.opcodeExecute();
    }

    return 0;
}


