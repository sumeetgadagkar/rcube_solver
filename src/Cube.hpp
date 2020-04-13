//
// Created by sumeet on 12/04/20.
//

#ifndef RCUBE_SOLVER_CUBE_HPP
#define RCUBE_SOLVER_CUBE_HPP

#include "Face.hpp"
#include <vector>
#include <string>
#include <iostream>

const std::vector<std::string> validMoves{"U", "R", "F", "D", "L", "B", // NOLINT(cert-err58-cpp)
                                    "U'", "R'", "F'", "D'", "L'", "B'",
                                    "U2", "R2", "F2", "D2", "L2", "B2",
                                    "u", "r", "f", "d", "l", "b",
                                    "u'", "r'", "f'", "d'", "l'", "b'",
                                    "M", "M'", "E", "E'", "S", "S'",
                                    "x", "x'", "y", "y'", "z", "z'"};

class Cube{

public:
    std::vector<std::string> solution;
    std::vector<Face> faces;

    Cube();
    void randomizeCube();
    void printCube(bool pretty = false, bool is256ColorSupported = false);
    void makeMove(const std::string& move);
    void swapRowCols(int f1, int f2, int rowCol_1, int rowCol_2, bool invertOrder = false);

protected:
    static void prettyPrint(int num, bool is256ColorSupported);
};

#endif //RCUBE_SOLVER_CUBE_HPP

