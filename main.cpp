/*
 * C++ program to illustrating a 3x3 rubik cube solver.
 * Author : zoroppz
 */

#include "src/Cube.hpp"

int main(int argc, char** argv){

    // instantiate cube object
    Cube myCube;

    // container to store the moves made
    std::vector<std::string> movesMade;

    // randomize the cube
    myCube.randomizeCube(&movesMade);

    // print the chosen moves
    for (const auto& move : movesMade){
        printf("%s ", move.c_str());
    }

    // print the cube
    myCube.printCube(true, true);
    return 0;
}