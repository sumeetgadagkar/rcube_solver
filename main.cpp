/*
 * C++ program to illustrating a 3x3 rubik cube solver.
 * Author : zoroppz
 */

#include "src/Cube.hpp"

int main(int argc, char** argv){

    // create initial cube state vector
    std::vector<int> cubeState {0, 0, 0, 4, 0, 3, 0, 2, 2,
                                1, 5, 4, 1, 1, 4, 2, 3, 2,
                                5, 0, 5, 0, 2, 3, 2, 2, 0,
                                3, 5, 3, 1, 3, 1, 1, 3, 4,
                                1, 5, 4, 1, 4, 2, 3, 4, 4,
                                5, 2, 5, 0, 5, 5, 3, 4, 1};

    // instantiate cube object
    Cube myCube(cubeState);

    // print cube
    myCube.printCube(true, true);

    return 0;
}