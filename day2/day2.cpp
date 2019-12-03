#include <QDebug>
#include <functional>
#include "data.h"
#include "day2.h"

namespace {
bool run(std::vector<int> &memory) {
    int ip = 0;
    bool halt = false;
    bool fail = false;

    auto fetch = [&memory](int address, int & value) -> bool {
        if(address < 0 || address >= memory.size()) {
            qCritical() << "Out of bounds fetch:" << address;
            return false;
        }
        value = memory[address];
        return true;
    };
    auto store = [&memory](int address, int value) -> bool {
        if(address < 0 || address >= memory.size()) {
            qCritical() << "Out of bounds store:" << address;
            return false;
        }
        memory[address] = value;
        return true;
    };

    while (!halt && !fail) {

        int instruction;
        if(!fetch(ip, instruction)){
            fail = true;
            break;
        }
        switch(instruction) {
            case 1:
            {
                int input1, input2, output;
                fail = !fetch(ip+1, input1);
                fail |= !fetch(input1, input1);
                fail |= !fetch(ip+2, input2);
                fail |= !fetch(input2, input2);
                fail |= !fetch(ip+3, output);
                fail |= !store(output, input1 + input2);
                ip+=4;
                break;
            }
            case 2:
            {
                int input1, input2, output;
                fail = !fetch(ip+1, input1);
                fail |= !fetch(input1, input1);
                fail |= !fetch(ip+2, input2);
                fail |= !fetch(input2, input2);
                fail |= !fetch(ip+3, output);
                fail |= !store(output, input1 * input2);
                ip+=4;
                break;
            }
            case 99:
            {
                halt = true;
                ip++;
                break;
            }
            default:
                qCritical() << "Invalid instruction" << instruction << "at address" << ip;
                fail = true;
                break;

        }
    }
    return (!fail);
}

bool runDefaultProgram(int noun, int verb, int& result) {
    std::vector<int> memory(program.begin(), program.end());
    memory[1] = noun;
    memory[2] = verb;

    if (!run(memory)) {
        return false;
    }
    result = memory[0];
    return true;
}

}

bool Day2::test() {
    // invalid memory on fetch
    {
        std::vector<int> memory = {
            1,100,10,3,
            2,3,11,0,
            99,
            30,40,50
        };
        if(run(memory)) {
            qCritical() << "Unexpected success, invalid fetch not caught.";
            return false;
        }
    }

    // invalid memory on store
    {
        std::vector<int> memory = {
            1,9,10,100,
            2,3,11,0,
            99,
            30,40,50
        };
        if(run(memory)) {
            qCritical() << "Unexpected success, invalid store not caught.";
            return false;
        }
    }

    // invalid instruction
    {
        std::vector<int> memory = {
            1,9,10,3,
            2,3,11,0,
            1,1,1,1,
            30,40,50
        };
        if(run(memory)) {
            qCritical() << "Unexpected success, invalid instruction not caught.";
            return false;
        }
    }

    // lack of halt instruction
    {
        std::vector<int> memory = {
            1,1,2,3,
            2,3,2,0
        };
        if(run(memory)) {
            qCritical() << "Unexpected success, instruction read past end of memory not caught.";
            return false;
        }
    }

    // positive test of functionality
    {
        std::vector<int> memory = {
            1,9,10,3,
            2,3,11,0,
            99,
            30,40,50
        };
        bool success = run(memory);
        success &= (memory[3] == 70);
        success &= (memory[0] == 3500);
        return success;
    }
}

bool Day2::PartOne() {
    int output;
    if(!runDefaultProgram(12, 2, output)) {
        return false;
    }
    qDebug() << "Day 2" << "Part 1:" << output;
    return true;
}

bool Day2::PartTwo()
{
    for(int noun = 0; noun < 100; noun++) {
        for(int verb = 0; verb < 100; verb++) {
            int output;
            if(!runDefaultProgram(noun, verb, output)) {
                // program failed for combination... ignore combination
                continue;
            }
            if (output == 19690720) {
                qDebug() << "Day 2" << "Part 2:" << (100 * noun + verb);
                return true;
            }
        }
    }
    qCritical() << "Day 2" << "Part 2:" << "No result found!";
    return false;
}
