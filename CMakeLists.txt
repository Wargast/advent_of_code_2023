cmake_minimum_required(VERSION 3.0.0)
project(AoC_2K23 VERSION 0.1.0 LANGUAGES C CXX)
# include_directories(include)

include(CTest)
enable_testing()

add_executable(day1 
  src/day1.cpp
)
add_executable(day2 
  src/day2.cpp
)
add_executable(day3
  src/day3.cpp
)
add_executable(day4
  src/day4.cpp
)
add_executable(day6 
  src/day6.cpp
)

add_executable(day5
  src/day5.cpp
)

add_executable(day7
  src/day7.cpp
)

add_executable(day8
  src/day8.cpp
)
add_executable(day9
  src/day9.cpp
)
# target_include_directories(AoC_2K23 PRIVATE src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
