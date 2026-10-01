//
// Created by yash on 10/1/26.
//

#include "cpu.h"
#include <print>

CPU::CPU()
{
    std::println("CPU created");
}

void CPU::loadProgram(char* filePath)
{
    std::println("Program loaded: {}", filePath);
}

void CPU::run()
{
    std::println("Program running");
}