cmake_minimum_required(VERSION 3.26)

project("Bin to Array")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE "bin_to_array")
file(GLOB_RECURSE SRC_FILES "src/**.cpp")
add_executable(${EXECUTABLE} ${SRC_FILES})

install(TARGETS ${EXECUTABLE} DESTINATION .)
