#include "chip8.h"

void chip8::loadRom(std::string romName) {
    // Copy ROM memory to console memory.
    std::cout << "[+] ROM " << romName << " copied" << std::endl;
};

void chip8::initializeConsole() {
    // Initialize registers, memory.
};

void chip8::emulateCycle() {
    // Fetch Opcode
    // Decode Opcode
    // Execute Opcode
    // Update Timers
};

void chip8::opcodeFetch(uint8_t * memLocation) {
    printf("%#x\n", *((uint8_t *)memLocation));
    printf("%#x\n", *((uint8_t *)memLocation) + 1);
};

void chip8::opcodeDecode() {
};

void chip8::opcodeExecute() {
};


