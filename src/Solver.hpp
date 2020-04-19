//
// Created by sumeet on 17/04/20.
//

#ifndef RCUBE_SOLVER_SOLVER_HPP
#define RCUBE_SOLVER_SOLVER_HPP

#include "Cube.hpp"
#include <set>

class Solver {

public:
    explicit Solver(Cube &cube); // constructor
    std::vector<std::string> solveCube(); // solve the cube with the basic method

    Cube& cube; // the cube to be solved

private:
    int findFacePos(int face);
    void getFaceToTop(int face);
    void setWhiteEdges();
    void setFLCorners();
    int getCornerPos(int col1, int col2, int col3);
};


#endif //RCUBE_SOLVER_SOLVER_HPP
