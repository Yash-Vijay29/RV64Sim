#include "cpu.h"
#include <fstream>
#include <filesystem>
#include <print>
#include <stdexcept>

CPU::CPU()
    :memory(MEMORY_SIZE)
{
    std::println("CPU created.. allocating {} as memory to CPU", MEMORY_SIZE);
}

void CPU::loadProgram(const char* filePath)
{
    std::println("Program Reading started.. Reading {}", filePath);
    std::ifstream file(filePath,std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Could not open program file");
    }
    std::println("Program Read, allocating memory to Program");
    const auto fileSize = std::filesystem::file_size(filePath);
    if (LOAD_ADDRESS + fileSize > MEMORY_SIZE)
    {
        throw std::runtime_error("Program size exceeds memory size");
    }
    std::println("Program allocated memory successfully");

    file.read(reinterpret_cast<char*>(memory.data()+LOAD_ADDRESS), static_cast<std::streamsize>(fileSize));

    pc = LOAD_ADDRESS;
    std::println("Program loaded: {} ({} bytes)",filePath,fileSize);
}

void CPU::run()
{
    std::println("Program run beginning");
    while (pc + 3 < MEMORY_SIZE)
    {
        uint32_t instruction = fetch();
        decode(instruction);
        pc+=4;
    }

}

uint32_t CPU::fetch()
{
    uint32_t instruction = static_cast<uint32_t>(memory[pc]) | static_cast<uint32_t>(memory[pc+1]) << 8 | static_cast<uint32_t>(memory[pc+2]) << 16 | static_cast<uint32_t>(memory[pc+3]) << 24;
    return instruction;
}

void CPU::decode(uint32_t instruction)
{
    uint32_t opcode = instruction & 0x7F;
    uint32_t rd     = (instruction >> 7)  & 0x1F;
    uint32_t funct3 = (instruction >> 12) & 0x07;
    uint32_t rs1    = (instruction >> 15) & 0x1F;
    uint32_t rs2    = (instruction >> 20) & 0x1F;
    uint32_t funct7 = (instruction >> 25) & 0x7F;
    std::println("Opcode: {}, rd: {}, funct3: {}, rs1: {}, rs2: {}, funct7: {}",opcode,rd,funct3,rs1,rs2,funct7);
}
