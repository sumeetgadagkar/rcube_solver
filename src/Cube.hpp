/*
 * Declaration of Cube class to represent a rubik's cube
 * Author : zoroppz
 */

#ifndef RCUBE_SOLVER_CUBE_HPP
#define RCUBE_SOLVER_CUBE_HPP

#include "Face.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <random>
#include <chrono>

class Cube {

public:

    Cube(); // constructor
    explicit Cube(std::vector<int>& cubeState); // constructor which accepts initial state of the cube
    void makeMove(const std::string& move); // perform a single move on the cube e.g. <cube_obj>.makeMove("U")
    void makeMove(const std::initializer_list<std::string> &moves); // perform a set of moves on the cube
        // e.g. <cube_obj>.makeMove({"U", "R",...})
    void makeMove(const std::vector<std::string> &moves); // perform a set of moves on the cube
        // e.g. <cube_obj>.makeMove(<string vector of moves>)
    void printCube(bool pretty = false, bool is256ColorSupported = false); // print the current state of the cube
    void randomizeCube(std::vector<std::string>& movesMade); // randomly pick 20 valid moves from Cube::validMoves
        // and perform them on the cube and adds the moves made to <movesMade>
    void randomizeCube(); // randomly pick 20 valid moves from Cube::validMoves and perform them on the cube
    virtual ~Cube(); // destructor

    std::vector<Face> faces; // vector of class Face to represent the six faces of the cube
    // faces[0] - up face
    // faces[1] - front face
    // faces[2] - down face
    // faces[3] - back face
    // faces[4] - right face
    // faces[5] - left face


private:
    void swapRowCols(int f1, int f2, int rowCol_1, int rowCol_2, bool invertOrder = false); // swap rows and columns
        // of the cube
    static void prettyPrint(int num, bool is256ColorSupported); // pretty printing of cube state with colors
};

// all standard valid moves that can be performed on a standard 3x3 rubik's cube
const std::vector<std::string> validMoves{"U", "R", "F", "D", "L", "B", // NOLINT(cert-err58-cpp)
                                          "U'", "R'", "F'", "D'", "L'", "B'",
                                          "U2", "R2", "F2", "D2", "L2", "B2",
                                          "u", "r", "f", "d", "l", "b",
                                          "u'", "r'", "f'", "d'", "l'", "b'",
                                          "M", "M'", "E", "E'", "S", "S'",
                                          "x", "x'", "y", "y'", "z", "z'"};

#endif //RCUBE_SOLVER_CUBE_HPP

