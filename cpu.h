#pragma once
#include <cstdint>
#include <vector>

class CPU
{
    private:
        enum RiscvFormat
        {
            R_Type,
            I_Type,
            S_Type,
            B_Type,
            U_Type,
            J_Type,
            Unknown
        };
    public:
        CPU();
        void loadProgram(const char* filePath);
        void run();
        uint32_t fetch();
        void decode(uint32_t instruction);
        RiscvFormat classify(uint32_t opcode);
    private:
        static constexpr uint64_t LOAD_ADDRESS = 0x1000;
        static constexpr uint64_t MEMORY_SIZE = 64*1024*1024;
        std::vector<uint8_t> memory;
        uint64_t pc;
        uint64_t programEnd;
};