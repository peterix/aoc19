#include <QDebug>
#include <functional>
#include "data.h"
#include "day1.h"

bool Day1::PartOne() {
    int64_t accumulator = 0;
    for (auto & mass: moduleMasses) {
        accumulator += (mass / 3 - 2);
    }
    qDebug() << "Day 1" << "Part 1:" << accumulator;
    return accumulator == 3152038;
}

bool Day1::PartTwo() {
    auto fuelForMass = [](int mass) -> int {
        return mass / 3 - 2;
    };
    auto fuelForFuel = [&fuelForMass](int fuel) -> int {
        int step = fuel;
        int accumulator = 0;
        do {
            step = fuelForMass(step);
            if(step <= 0) {
                break;
            }
            accumulator += step;
        } while (true);
        return accumulator;
    };

    int64_t accumulator = 0;
    for (auto & mass: moduleMasses) {
        int64_t fuel = fuelForMass(mass);
        fuel += fuelForFuel(fuel);
        accumulator += fuel;
    }
    qDebug() << "Day 1" << "Part 2:" << accumulator;
    return accumulator == 4725210;
}
