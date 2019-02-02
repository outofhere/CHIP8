#include <stdio.h>
#include <stdint.h>
#include <array>

class chip8 {
public:
    // 4kb of memory to work with.
    std::array<uint8_t, 4096> memoryLayout;

    // 16 semi-general purpose registers.
    std::array<uint8_t, 16> V0; // VF used for carry flag and some other stuff.

    // Program counter(pc) and address register(I).
    uint16_t pc;
    uint16_t I;

    // Graphics output scales with 64x32 screen and also black and white.
    std::array<uint8_t, 64*32> graph;

    // Timer registers. One for delay and one for sound.
    uint8_t delay_timer;
    uint8_t sound_timer;

    // Stack. At least 16 levels. Original implementation was 24 levels.
    std::array<uint16_t, 48> stack;

    // Stack pointer register(sp).
    uint16_t sp;

    // Chip8 has HEX-based keypad
    std::array<uint8_t, 16> key;

    // Set of functions used for emulation.
    void loadRom(std::string);
    void initializeConsole();
    void emulateCycle();
    void opcodeFetch(uint8_t * memLocation);
    void opcodeDecode();
    void opcodeExecute();
};
