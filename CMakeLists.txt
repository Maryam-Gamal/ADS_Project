#cmake_minimum_required(VERSION 3.26)
#project(Assignment1WithAnswers)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(Assignment1WithAnswers main.cpp)


cmake_minimum_required(VERSION 3.26)
project(testing_test)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(Code_lib_run ${SOURCE_FILES})

include_directories(Code_lib)
add_subdirectory(Code_lib)

target_link_libraries(Code_lib_run Code_lib)

add_subdirectory(Google_tests)