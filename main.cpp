/*
 * C++ program to illustrating a 3x3 rubik cube solver.
 * Author : zoroppz
 */

#include "src/Cube.hpp"
#include "src/Solver.hpp"

int main(int argc, char **argv) {
    // instantiate cube object
    Cube myCube;

    // print the cube
    printf("\nInitial cube state :\n");
    myCube.printCube(true, true);

    // container to store randomizing moves
    std::vector<std::string> movesMade;

    // randomize the cube
    myCube.randomizeCube(movesMade);

    // print the randomizing moves
    printf("\nRandomizing moves : ");

    for (const auto &move : movesMade) {
        printf("%s ", move.c_str());
    }
    printf("\n");
    // start recording moves
    myCube.startMoveRecording(true);

    // print the cube
    printf("\nShuffled cube :\n");
    myCube.printCube(true, true);

    // instantiate the solver
    Solver mySolver(myCube);

    // solve the cube
    mySolver.solveCube();

    // stop recording the moves
    myCube.stopMoveRecording();

    // print the cube
    printf("\nSolved cube :\n");
    myCube.printCube(true, true);

    // print solution
    printf("Number of moves made : %zu\nSolution : ", myCube.recordedMoves.size());

    for (const auto& move : myCube.recordedMoves) {
        printf("%s ", move.c_str());
    }
    printf("\n");

    return 0;
}