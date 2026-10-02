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
    programEnd = LOAD_ADDRESS + fileSize;
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
    std::println("Instruction classification start");
    uint32_t opcode = instruction & 0x7F;
    uint8_t type = classify(opcode); // look at classify function to see what type of instruction it corresponds to
    // todo: Add helper type specific decoder and execution functions
    //std::println("Opcode: {}, rd: {}, funct3: {}, rs1: {}, rs2: {}, funct7: {}",opcode,rd,funct3,rs1,rs2,funct7);
}

uint8_t CPU::classify(uint32_t opcode)
{
    switch (opcode)
    {
        case 0b0110011: return 0; break; // R type
        case 0b0010011: return 1; break; // I type
        case 0b0011011: return 2; break; // I type 64 bit word
        case 0b0000011: return 3; break; // I type Load
        case 0b1100111: return 4; break; // I type Jump
        case 0b0100011: return 5; break; // S type
        case 0b1100011: return 6; break; // SB type
        case 0b0110111: return 7; break; // U type load immediate
        case 0b0010111: return 8; break; // U type add upper immediate
        case 0b1101111: return 9; break; // U J type Jump and Link
        case 0b1110011: return 10; break; // I type Enviroment
    }
    throw std::runtime_error("Invalid opcode");
    return 11;
}
