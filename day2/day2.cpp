#include <QDebug>
#include <functional>
#include "data.h"
#include "day2.h"

namespace {
bool run(std::vector<int> &memory) {
    int ip = 0;
    bool halt = false;
    bool fail = false;

    auto fetch = [&memory](int offset, int & value) -> bool {
        if(offset < 0 || offset >= memory.size()) {
            qCritical() << "Out of bounds fetch:" << offset;
            return false;
        }
        value = memory[offset];
        return true;
    };
    auto store = [&memory](int offset, int value) -> bool {
        if(offset < 0 || offset >= memory.size()) {
            qCritical() << "Out of bounds store:" << offset;
        }
        memory[offset] = value;
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
                int input1, input2, offset;
                fail &= !fetch(ip+1, input1);
                fail &= !fetch(input1, input1);
                fail &= !fetch(ip+2, input2);
                fail &= !fetch(input2, input2);
                fail &= !fetch(ip+3, offset);
                fail &= !store(offset, input1 + input2);
                ip+=4;
                break;
            }
            case 2:
            {
                int input1, input2, offset;
                fail &= !fetch(ip+1, input1);
                fail &= !fetch(input1, input1);
                fail &= !fetch(ip+2, input2);
                fail &= !fetch(input2, input2);
                fail &= !fetch(ip+3, offset);
                fail &= !store(offset, input1 * input2);
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

}

bool Day2::test() {
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

bool Day2::PartOne() {
    std::vector<int> memory(program.begin(), program.end());

    memory[1] = 12;
    memory[2] = 2;

    bool success = run(memory);

    qDebug() << "Day 2" << "Part 1:" << memory[0];
    return success;
}

bool Day2::PartTwo()
{
    for(int noun = 0; noun < 100; noun++) {
        for(int verb = 0; verb < 100; verb++) {
            std::vector<int> memory(program.begin(), program.end());
            memory[1] = noun;
            memory[2] = verb;

            if (!run(memory)) {
                continue;
            }
            if (memory[0] == 19690720) {
                qDebug() << "Day 2" << "Part 2:" << (100 * noun + verb);
                return true;
            }
        }
    }
    qCritical() << "Day 2" << "Part 2:" << "No result found!";
    return false;
}
