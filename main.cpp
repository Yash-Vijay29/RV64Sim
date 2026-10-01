#include <print>
#include<exception>
#include "cpu.h"
#include <cstdio>
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::println(stderr,"Usage: fakecpu <program.bin>");
        return 1;
    }
    try
    {
        CPU cpu;
       cpu.loadProgram(argv[1]);
       cpu.run();
    } catch (const std::exception& e){
        std::println(stderr,"Simulation has errored lol: {}", e.what());
        return 1;
    }

    return 0;
}