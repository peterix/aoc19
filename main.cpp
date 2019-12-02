#include <QString>

#include "log.h"

#include "day1/day1.h"
#include "day2/day2.h"

std::vector<std::function<bool()>> parts = {
    &Day1::PartOne,
    &Day1::PartTwo,
    &Day2::test,
    &Day2::PartOne,
    &Day2::PartTwo
};

int main(int argc, char *argv[])
{
    initLog();

    int partNr = 1;
    for(auto & part: parts) {
        if(!part()) {
            qCritical() << "Part" << partNr << "failed!";
            return 1;
        }
        partNr ++;
    }

    return 0;
}
