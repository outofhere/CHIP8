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

uint16_t chip8::opcodeFetch(uint8_t * memLocation) {
    if ((uintptr_t)memLocation % 2 == 0) {
        uint16_t opcode = 0;
        opcode = *((uint8_t *)memLocation) << 8;
        opcode |= *((uint8_t *)memLocation + 1);
        return opcode;
    } else {
        printf ("[!] Pointer: %p\n", memLocation);
        throw std::runtime_error ("[-] Fetched opcode not aligned to 2\n");
        return -1;
    }
};

void chip8::opcodeDecode(uint16_t opcode) {
    printf ("[!] Executing opcode: %#0.4x\n", opcode);
    switch(opcode & 0xF000) {
        case 0x0000:
        // Opcode: 0NNN
        // Type: Call
        // Explanation: Calls RCA 1802 program at address NNN. Not necessary for most ROMs.

        // Opcode: 00E0
        // Type: Display disp_clear()
        // Explanation: Clears the screen.

        // Opcode: 00EE
        // Type: Flow return;
        // Explanation: Returns from a subroutine.
            if (opcode == 0x00EE) {
                printf ("[!] RET instruction\n");
                pc = stack.at(sp);
                --sp;
            } else if (opcode == 0x00E0) {
                printf ("[!] CLRSCR instruction\n");
                pc += 2;
            } else {
                printf ("[!] CALL instruction\n");
                ++sp;
                pc += 2;
                stack.at(sp) = pc;
                pc = opcode;
            }
            break;

        // Type: 1NNN
        // Type: Flow goto NNN;
        // Explanation: Jumps to address NNN.
        case 0x1000:
            printf ("[!] JMP instruction!\n");
            pc = opcode & 0x0FFF;
            break;

        // Type: 2NNN
        // Type: Flow *(0xNNN)()
        // Explanation: Calls subroutine at NNN.
        case 0x2000:
            printf ("[!] CALL instruction\n");
            ++sp;
            pc += 2;
            stack.at(sp) = pc;
            pc = opcode & 0x0FFF;
            break;

        // Type: 3XNN
        // Type: Cond if(Vx!=NN)
        // Explanation: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
        case 0x3000:
            printf ("[!] Success!\n");
            if (V.at((opcode & 0x0F00) >> 8) == opcode & 0x00FF) {pc += 0x4;}
            break;

        // Type: 4XNN
        // Type: Cond if(Vx==NN)
        // Explanation: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
        case 0x4000:
            printf ("[!] Success!\n");
            if (V.at((opcode & 0x0F00) >> 8) != opcode & 0x00FF) {pc += 0x4;}
            break;

        // Type: 5XY0
        // Type: Cond if(Vx!=Vy)
        // Explanation: Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block
        case 0x5000:
            printf ("[!] Success!\n");
            if (V.at((opcode & 0x0F00) >> 8) == V.at((opcode & 0x00F0) >> 8)) {pc += 0x4;}
            break;

        default:
            printf ("[!] Opcode: %#0.4x\n", opcode);
            throw std::runtime_error ("[-] Opcode is not implemented\n");
    }
};

void chip8::opcodeExecute() {
    opcodeDecode(opcodeFetch(&memoryLayout[pc]));
    debugPrint();
};

void chip8::postStep() {
}

void chip8::debugPrint() {
    printf("pc_value: %#0.4x\n", pc);
    printf("sp_value: %#0.4x, stack_level: %d\n", stack[sp], sp);
}

