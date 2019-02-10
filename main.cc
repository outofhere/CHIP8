#include <stdio.h>
#include <iostream>
#include "chip8.cc"

int main(int argc, const char **argv) {
    chip8 console;
    std::cout << "[*] Starting program" << std::endl;
    console.loadRom("test");
/*

Program 0x0: Jumping randomly
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

Program 0x1:  Jumping over code if equal to immidiate
    console.memoryLayout[0x200] = 0x60;
    console.memoryLayout[0x201] = 0x77;  // mov v0, 0x77
    console.memoryLayout[0x202] = 0x30;
    console.memoryLayout[0x203] = 0x77;  // je(v0, 0x77) 0x2
    console.memoryLayout[0x204] = 0x61;
    console.memoryLayout[0x205] = 0x66;  // mov v0, 0x66
    console.memoryLayout[0x206] = 0x61;
    console.memoryLayout[0x207] = 0x99;  // mov v1, 0x99
    console.memoryLayout[0x208] = 0x61;
    console.memoryLayout[0x209] = 0x99;  // mov v1, 0x99

Program 0x2:  Jumping over code if equal registers
    console.memoryLayout[0x200] = 0x60;
    console.memoryLayout[0x201] = 0x77;  // mov v0, 0x77
    console.memoryLayout[0x202] = 0x61;
    console.memoryLayout[0x203] = 0x76;  // mov v0, 0x77
    console.memoryLayout[0x204] = 0x51;
    console.memoryLayout[0x205] = 0x00;  // je(v1, v0) 0x4
    console.memoryLayout[0x206] = 0x60;
    console.memoryLayout[0x207] = 0x33;  // mov v0, 0x33
    console.memoryLayout[0x208] = 0x61;
    console.memoryLayout[0x209] = 0x99;  // mov v1, 0x99
    console.memoryLayout[0x20A] = 0x61;
    console.memoryLayout[0x20B] = 0x99;  // mov v1, 0x99

Program 0x3: Adding some values to registers
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x70;
    console.memoryLayout[0x203] = 0x02;  // mov v0, 0x02
    console.memoryLayout[0x204] = 0x71;
    console.memoryLayout[0x205] = 0x06;  // mov v1, 0x06

Program 0x4: mov v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x10;  // mov v0, v1

Program 0x5: or v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x11;  // or v0, v1

Program 0x6: and v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x12;  // and v0, v1

Program 0x7: xor v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x03;  // mov v0, 0x03
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x13;  // xor v0, v1

Program 0x8: addc v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0xFF;  // mov v1, 0xFF
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x14;  // addc v0, v1

Program 0x9: subc v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x15;  // subc v0, v1

Program 0xA: mov v0, v1
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x10;  // mov v0, v1


*/
    console.memoryLayout[0x200] = 0x70;
    console.memoryLayout[0x201] = 0x01;  // mov v0, 0x01
    console.memoryLayout[0x202] = 0x71;
    console.memoryLayout[0x203] = 0x02;  // mov v1, 0x02
    console.memoryLayout[0x204] = 0x80;
    console.memoryLayout[0x205] = 0x15;  // subc v0, v1
    for (uint8_t i; i < 3; ++i) {
        console.opcodeExecute();
    }
    return 0;
}


