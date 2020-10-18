cmake_minimum_required(VERSION "3.18.4")

project("Earraper")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("vendor/")

add_executable("Earraper.exe" "src/Earraper.cpp")