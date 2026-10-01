//
// Created by yash on 10/1/26.
//

#include "cpu.h"
#include <fstream>
#include <filesystem>
#include <print>

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
        std::println(stderr,"Error Reading program: {}", filePath);
        return;
    }
    std::println("Program Read, allocating memory to Program");
    const auto fileSize = std::filesystem::file_size(filePath);
    if (LOAD_ADDRESS + fileSize > MEMORY_SIZE)
    {
        std::println(stderr,"Error: Program size exceeds memory size");
        return;
    }
    std::println("Program allocated memory successfully");

    file.read(reinterpret_cast<char*>(memory.data()+LOAD_ADDRESS), static_cast<std::streamsize>(fileSize));


    pc = LOAD_ADDRESS;
    std::println("Program loaded: {} ({} bytes)",filePath,fileSize);
}

void CPU::run()
{
    std::println("Program running");
}