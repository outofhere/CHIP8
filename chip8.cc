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
        case 0x0000: {
        // Opcode: 0NNN
        // Explanation: Calls RCA 1802 program at address NNN. Not necessary for most ROMs.

        // Opcode: 00E0
        // Explanation: Clears the screen.

        // Opcode: 00EE
        // Explanation: Returns from a subroutine.
            if (opcode == 0x00EE) {
                printf ("[!] ret\n");
                pc = stack.at(sp);
                --sp;
            } else if (opcode == 0x00E0) {
                printf ("[!] clrscr\n");
                pc += 2;
            } else {
                ++sp;
                pc += 2;
                stack.at(sp) = pc;
                pc = opcode;
                printf ("[!] call %#0.4x\n", pc);
            }
            break;
        }
        // Type: 1NNN
        // Explanation: Jumps to address NNN.
        case 0x1000: {
            pc = opcode & 0x0FFF;
            printf ("[!] jmp %#0.4x\n", pc);
            break;
        }

        // Type: 2NNN
        // Explanation: Calls subroutine at NNN.
        case 0x2000: {
            ++sp;
            pc += 2;
            stack.at(sp) = pc;
            pc = opcode & 0x0FFF;
            printf ("[!] call %#0.4x\n", pc);
            break;
        }

        // Type: 3XNN
        // Explanation: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
        case 0x3000: {
            printf ("[!] je(v%x, %#x) 0x4\n", (opcode & 0x0F00) >> 8, opcode & 0x00FF);
            if (V.at((opcode & 0x0F00) >> 8) == (uint8_t)opcode & 0x00FF) {
                pc += 0x4;
            } else {
                pc += 0x2;
            }
            break;
        }

        // Type: 4XNN
        // Explanation: Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
        case 0x4000: {
            printf ("[!] jne(v%x, %#x) 0x4\n", (opcode & 0x0F00) >> 8, opcode & 0x00FF);
            if (V.at((opcode & 0x0F00) >> 8) != (uint8_t)opcode & 0x00FF) {
                pc += 0x4;
            } else {
                pc += 0x2;
            }
            break;
        }

        // Type: 5XY0
        // Explanation: Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block
        case 0x5000: {
            printf ("[!] je(v%x, v%x) 0x4\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
            if (V.at((opcode & 0x0F00) >> 8) == V.at((opcode & 0x00F0) >> 8)) {
                pc += 0x4;
            } else {
                pc += 0x2;
            }
            break;
        }

        // Type: 6XNN
        // Explanation: Sets VX to NN
        case 0x6000: {
            printf ("[!] mov v%x, %#x\n", (opcode & 0x0F00) >> 8, opcode & 0x00FF);
            V.at((opcode & 0x0F00) >> 8) = opcode & 0x00FF;
            pc += 0x2;
            break;
        }

        // Type: 7XNN
        // Explanation: Adds NN to VX. (Carry flag is not changed)
        case 0x7000: {
            printf ("[!] add v%x, %#x\n", (opcode & 0x0F00) >> 8, opcode & 0x00FF);
            V.at((opcode & 0x0F00) >> 8) += (uint8_t)(opcode & 0x00FF);
            pc += 2;
            break;
        }

        // Type: 8XY0
        // Explanation: Sets VX to the value of VY.

        // Type: 8XY1
        // Explanation: Sets VX to VX or VY. (Bitwise OR operation)

        // Type: 8XY2
        // Explanation: Sets VX to VX and VY. (Bitwise AND operation)

        // Type: 8XY3
        // Explanation: Sets VX to VX xor VY.

        // Type: 8XY4
        // Explanation: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.

        // Type: 8XY5
        // Explanation: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

        // Type: 8XY6
        // Explanation: Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[2]

        // Type: 8XY7
        // Explanation: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

        // Type: 8XYE
        // Explanation: Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
        case 0x8000: {
            uint8_t lastDigit = opcode & 0x000F;
            switch (lastDigit) {
                case 0x0: {
                    printf ("OPCODE %x\n", (opcode & 0x00f0) >> 8);
                    printf ("[!] mov v%x, v%x\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    V.at((opcode & 0x0F00) >> 8) = V.at((opcode & 0x00F0) >> 4);
                    pc += 2;
                    break;
                }
                case 0x1: {
                    printf ("[!] or v%x, v%x\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    V.at((opcode & 0x0F00) >> 8) |= V.at((opcode & 0x00F0) >> 4);
                    pc += 2;
                    break;
                }
                case 0x2: {
                    printf ("[!] and v%x, v%x\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    V.at((opcode & 0x0F00) >> 8) &= V.at((opcode & 0x00F0) >> 4);
                    pc += 2;
                    break;
                }
                case 0x3: {
                    printf ("[!] xor v%x, v%x\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    V.at((opcode & 0x0F00) >> 8) ^= V.at((opcode & 0x00F0) >> 4);
                    pc += 2;
                    break;
                }
                // (TODO) Fix this.
                case 0x4: {
                    printf ("[!] addc v%x, v%x\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    uint8_t tmp = (V.at((opcode & 0x0F00) >> 8) != 0) ? V.at((opcode & 0x0F00) >> 8) : V.at((opcode & 0x00F0) >> 4);
                    V.at((opcode & 0x0F00) >> 8) += V.at((opcode & 0x00F0) >> 4);
                    // If register overlaps, result is less than both of the operands.
                    if (V.at((opcode & 0x0F00) >> 8) < tmp) {
                        V.at(0xF) = 1;
                    } else {
                        V.at(0xF) = 0;
                    }
                    pc += 2;
                    break;
                }
                case 0x5: {
                    printf ("[!] subc v%x, v%x\n", (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    if (V.at((opcode & 0x0F00) >> 8) < V.at((opcode & 0x00F0) >> 4)) {
                        V.at(0xF) = 1;
                    } else {
                        V.at(0xF) = 0;
                    }
                    V.at((opcode & 0x0F00) >> 8) -= V.at((opcode & 0x00F0) >> 4);
                    pc += 2;
                    break;
                }
                case 0x6: {
                    break;
                }
                case 0x7: {
                    break;
                }
                case 0xE: {
                    break;
                }
            }

            break;
        }
        case 0x9000: {
            printf ("[!] Success!\n");
            if (V.at((opcode & 0x0F00) >> 8) == V.at((opcode & 0x00F0) >> 8)) {pc += 0x4;}
            break;
        }
        case 0xA000: {
            printf ("[!] Success!\n");
            if (V.at((opcode & 0x0F00) >> 8) == V.at((opcode & 0x00F0) >> 8)) {pc += 0x4;}
            break;
        }
        default: {
            printf ("[!] Opcode: %#0.4x\n", opcode);
            throw std::runtime_error ("[-] Opcode is not implemented\n");
        }
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
    printf("v0: %#0.2x\n", V.at(0x0));
    printf("v1: %#0.2x\n", V.at(0x1));
    printf("vf: %#0.2x\n", V.at(0xf));
}

