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
    std::println("Program Reading started.. Reading file {}", filePath);
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
    RiscvFormat type = classify(opcode); // look at classify function to see what type of instruction it corresponds to
    // todo: Add helper type specific decoder and execution functions
    //std::println("Opcode: {}, rd: {}, funct3: {}, rs1: {}, rs2: {}, funct7: {}",opcode,rd,funct3,rs1,rs2,funct7);
}

CPU::RiscvFormat CPU::classify(uint32_t opcode)
{
    opcode = (opcode >> 2) & 0x1F;
    switch (opcode) {
    case 0b01100: [[fallthrough]];
    case 0b01110: [[fallthrough]];
    case 0b01111: return RiscvFormat::R_Type;
    case 0b00000: [[fallthrough]]; // Loads
    case 0b00100: [[fallthrough]];
    case 0b00110: [[fallthrough]];
    case 0b11001: [[fallthrough]];
    case 0b11100: return RiscvFormat::I_Type;
    case 0b01000: [[fallthrough]];
    case 0b01001: return RiscvFormat::S_Type;
    case 0b11000: return RiscvFormat::B_Type;
    case 0b01101: [[fallthrough]];
    case 0b00101: return RiscvFormat::U_Type;
    case 0b11011: return RiscvFormat::J_Type;
    default:      return RiscvFormat::Unknown;
    }
    throw std::runtime_error("Invalid Error");
}
