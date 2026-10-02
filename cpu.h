#pragma once
#include <cstdint>
#include <vector>

class CPU
{
    public:
        CPU();
        void loadProgram(const char* filePath);
        void run();
        uint32_t fetch();
        void decode(uint32_t instruction);
    private:
        static constexpr uint64_t LOAD_ADDRESS = 0x1000;
        static constexpr uint64_t MEMORY_SIZE = 64*1024*1024;
        std::vector<uint8_t> memory;
        uint64_t pc;
};