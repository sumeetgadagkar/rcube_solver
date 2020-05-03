/*
 * Declaration of Solver class to solve a rubik's cube
 * Author : zoroppz
 */

#ifndef RCUBE_SOLVER_SOLVER_HPP
#define RCUBE_SOLVER_SOLVER_HPP

#include "Cube.hpp"
#include <set>

class Solver {

public:
    explicit Solver(Cube &cube); // constructor
    std::vector<std::string> solveCube(); // solve the cube with the basic method

    Cube &cube; // the cube to be solved

private:
    int findFacePos(int face); // find the position of the face <face> in <cube>
    void getFaceToTop(int face); // make moves on <cube> to get face <face> on top
    void setWhiteEdges(); // form the daisy and then form the white cross
    void setFLCorners(); // set and orient the white(first) layer corners thereby solving the first layer
    int getCornerPos(int col1, int col2, int col3); // find the corner with colors : col1, col2, col3 and return the
    // position
    void setSLEdges(); // set the second layer edges
    void setLLCorners(); // set the last layer corners
    int getLLPattern(); // get the pattern of the yellow edges on the last layer
    int getCornersSet(); // get the number of top layer corners set correctly
    int getSetCornerPosition(); // get the state of the last layer corners
    void setLLEdges(); // set the ast layer edges
    int getLLEdgeState(); // get the state of the last layer edges
};


#endif //RCUBE_SOLVER_SOLVER_HPP
