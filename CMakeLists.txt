cmake_minimum_required(VERSION 3.26)
project(PuzzlePathfinder)

set(CMAKE_CXX_STANDARD 17)

add_executable(PuzzlePathfinder main.cpp
        IStateGenerator.h
        FarmerPuzzle.cpp
        FarmerPuzzle.h
        PuzzleSolver.cpp
        PuzzleSolver.h
)

include_directories(C:/Dev/Libraries/GraphPathfinding)

target_link_libraries(PuzzlePathfinder PRIVATE C:/Dev/Libraries/GraphPathfinding/cmake-build-debug/libgraph.a)