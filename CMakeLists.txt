cmake_minimum_required(VERSION 3.15)

project(aoc19 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

SET(DAY_CODE
    day1/data.h
    day1/day1.h
    day1/day1.cpp

    day2/data.h
    day2/day2.h
    day2/day2.cpp
)

add_executable(aoc19 main.cpp log.cpp log.h ${DAY_CODE})
target_link_libraries(aoc19 Qt5::Core)
install(TARGETS aoc19 RUNTIME DESTINATION bin)