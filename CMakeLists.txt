cmake_minimum_required(VERSION 3.21)
project(Condorcet)

set(CMAKE_CXX_STANDARD 14)

add_executable(Condorcet main.cpp Candidate.cpp Candidate.h)
