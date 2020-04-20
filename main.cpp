/*
 * C++ program to illustrating a 3x3 rubik cube solver.
 * Author : zoroppz
 */

#include "src/Cube.hpp"
#include "src/Solver.hpp"

int main(int argc, char **argv) {
    // instantiate cube object
    Cube myCube;

    //myCube.makeMove({"l", "L2", "d'", "f'", "M", "r'", "r", "M'", "y", "l'", "M'", "y'", "F2", "E'", "y'", "b", "f'", "F'", "u'", "d'"});

    // container to store randomizing moves
    std::vector<std::string> movesMade;

    // randomize the cube
    myCube.randomizeCube(movesMade);

    // print the randomizing moves
    printf("{");
    for (const auto &move : movesMade) {
        printf("\"%s\", ", move.c_str());
    }
    printf("}");

    // print the cube
    myCube.printCube(true, true);

    // instantiate the solver
    Solver mySolver(myCube);

    // solve the cube
    mySolver.solveCube();

    // print the cube
    mySolver.cube.printCube(true, true);

    return 0;
}