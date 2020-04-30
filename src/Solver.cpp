/*
 * Definition of Solver class
 * Author : zoroppz
 */

#include "Solver.hpp"

Solver::Solver(Cube &cube) : cube(cube) {
    // instantiate solver with a cube reference
}

std::vector<std::string> Solver::solveCube() {
    // solve the cube with the basic method

    // step 1 : constructing the cross

    // get the yellow face to the top
    this->getFaceToTop(2);

    // form the daisy (yellow center with adjacent white edges)
    // align front, right, back and left centers with the corresponding top edges and bring the white edges down
    this->setWhiteEdges();

    // step 2 : solve the first layer (corners)
    this->setFLCorners();

    // step 3 : solve the second layer edges
    this->setSLEdges();

    // step 4 : set last layer corners
    this->setLLCorners();

    return std::vector<std::string>();
}

void Solver::getFaceToTop(int face) {
    // get the face <face> to the top
    int currentPos = this->findFacePos(face);
    std::vector<std::string> movesToPerform;
    switch (currentPos) {
        case 1:
            // face is present on front
            // perform move "X"
            movesToPerform = {"x"};
            break;
        case 2:
            // face is present on down
            // perform moves {"X", "X"}
            movesToPerform = {"x", "x"};
            break;
        case 3:
            // face is present on back
            // perform move "X'"
            movesToPerform = {"x'"};
            break;
        case 4:
            // face is present on right
            // perform move "Z'"
            movesToPerform = {"z'"};
            break;
        case 5:
            // face is present on left
            // perform move "Z"
            movesToPerform = {"z"};
            break;
        default:
            // face already on top
            // nothing to do
            break;

    }
    this->cube.makeMove(movesToPerform);
}

int Solver::findFacePos(int face) {
    int pos = -1;
    for (int i = 0; i < 6; i++) {
        if (face == this->cube.faces[i].state[1][1]) {
            pos = i;
        }
    }
    return pos;
}

void Solver::setWhiteEdges() {
    // check how many edges are already set
    int edgesSet = 0;
    if (this->cube.faces[0].state[0][1] == 0 || this->cube.faces[3].state[0][1] == 0) {
        edgesSet++;
    }
    if (this->cube.faces[0].state[1][2] == 0 || this->cube.faces[4].state[0][1] == 0) {
        edgesSet++;
    }
    if (this->cube.faces[0].state[1][0] == 0 || this->cube.faces[5].state[0][1] == 0) {
        edgesSet++;
    }

    // set the white edges to the top face
    int faceMoved = 0;
    while (edgesSet < 4) {
        while (faceMoved < 4) {
            if (this->cube.faces[0].state[2][1] == 0 || this->cube.faces[1].state[0][1] == 0) {
                edgesSet++;
                if (edgesSet >= 4) {
                    // all edges are placed
                    break;
                }
                this->cube.makeMove("U");
                // check if edge is already set
                while (this->cube.faces[0].state[2][1] == 0 || this->cube.faces[1].state[0][1] == 0) {
                    // edge was already counted move to next
                    this->cube.makeMove("U");
                }
            } else {
                // edge is not found move the front face
                this->cube.makeMove("F");
                faceMoved++;
            }
        }
        // all face edges exhausted
        // move bring in bottom two layers of the left face
        faceMoved = 0;
        this->cube.makeMove("d");
    }

    // orient the required white edges
    for (int i = 0; i < 4; i++) {
        if (this->cube.faces[0].state[2][1] != 0) {
            // the white edge is twisted
            this->cube.makeMove({"F", "U'", "R", "U"});
        }
        this->cube.makeMove("y");
    }

    // number of white edges put on the white face
    edgesSet = 0;

    while (edgesSet < 4) {
        if (this->cube.faces[1].state[0][1] == this->cube.faces[1].state[1][1]) {
            // center and edge match
            // move the edge to the bottom
            this->cube.makeMove("F2");
            edgesSet++;
            this->cube.makeMove("y");
        } else {
            // edge and center do not match
            // move bottom 2 layers
            this->cube.makeMove("d");
        }
    }
}

void Solver::setFLCorners() {
    // solve the first layer corners
    int cornersSet = 0;
    std::set<int> expectedColors{this->cube.faces[1].getCenter(), this->cube.faces[2].getCenter(),
                                 this->cube.faces[4].getCenter()};
    std::set<int> actualColors{this->cube.faces[1].state[2][2], this->cube.faces[2].state[0][2],
                               this->cube.faces[4].state[2][0]};
    while (cornersSet < 4) {
        // check if front face bottom right corner is set
        if (actualColors == expectedColors) {
            // corner is set
            cornersSet++;
            // bring in the bottom two layers from the right face
            this->cube.makeMove("d'");
            // reset expectedColors and actualColors
            expectedColors.clear();
            actualColors.clear();
            expectedColors.insert({this->cube.faces[1].getCenter(), this->cube.faces[2].getCenter(),
                                   this->cube.faces[4].getCenter()});
            actualColors.insert({this->cube.faces[1].state[2][2], this->cube.faces[2].state[0][2],
                                 this->cube.faces[4].state[2][0]});
        } else {
            // corner is not set
            // find the correct corner
            switch (this->getCornerPos(this->cube.faces[1].getCenter(), this->cube.faces[2].getCenter(),
                                       this->cube.faces[4].getCenter())) {
                case 0:
                    // already set do nothing
                    break;
                case 1:
                    this->cube.makeMove({"y'", "R", "U", "R'", "U'", "U'", "y", "R", "U", "R'", "U'"});
                    break;
                case 2:
                    this->cube.makeMove({"y'", "y'", "R", "U", "R'", "U'", "U'", "U'", "y", "y", "R", "U", "R'", "U'"});
                    break;
                case 3:
                    this->cube.makeMove({"y", "R", "U", "R'", "U'", "U", "y'", "R", "U", "R'", "U'"});
                    break;
                case 4:
                    this->cube.makeMove({"R", "U", "R'", "U'"});
                    break;
                case 5:
                    this->cube.makeMove({"U'", "R", "U", "R'", "U'"});
                    break;
                case 6:
                    this->cube.makeMove({"U2", "R", "U", "R'", "U'"});
                    break;
                case 7:
                    this->cube.makeMove({"U", "R", "U", "R'", "U'"});
                    break;
                default:
                    printf("\nThe cube is in an illegal state\n");
                    break;
            }
            // reset actualColors
            actualColors.clear();
            actualColors.insert({this->cube.faces[1].state[2][2], this->cube.faces[2].state[0][2],
                                 this->cube.faces[4].state[2][0]});
        }
    }

    // orient the first layer corners
    cornersSet = 0;
    while (cornersSet < 4) {
        // check if the front face bottom right corner is correctly oriented
        if ((this->cube.faces[1].getCenter() == this->cube.faces[1].state[2][2]) &&
            (this->cube.faces[2].getCenter() == this->cube.faces[2].state[0][2]) &&
            (this->cube.faces[4].getCenter() == this->cube.faces[4].state[2][0])) {
            // corner is correctly oriented
            cornersSet++;
            // bring in bottom two layers from the right face
            this->cube.makeMove("d'");
        } else {
            // corner is not oriented correctly
            // change the corner orientation
            this->cube.makeMove({"R", "U", "R'", "U'"});
        }
    }
}

int Solver::getCornerPos(int col1, int col2, int col3) {
    // get the position of the corner represented by the colors : col1, col2, col3

    // the position convention used is as described below
    //
    //          3 X 0
    //          X R X
    //          7 X 4
    //          - - -
    //  3 X 7 | 7 X 4 | 4 X 0 | 0 X 3
    //  X B X | X U X | X F X | X D X
    //  2 X 6 | 6 X 5 | 5 X 1 | 1 X 2
    //          - - -
    //          6 X 5
    //          X L X
    //          2 X 1

    std::set<int> colorsToFind{col1, col2, col3};

    // check position 0
    if (colorsToFind == std::set<int>{this->cube.faces[1].state[2][2], this->cube.faces[2].state[0][2],
                                      this->cube.faces[4].state[2][0]}) {
        return 0;
    }
        // check position 1
    else if (colorsToFind == std::set<int>{this->cube.faces[1].state[2][0], this->cube.faces[2].state[0][0],
                                           this->cube.faces[5].state[2][2]}) {
        return 1;
    }
        // check position 2
    else if (colorsToFind == std::set<int>{this->cube.faces[5].state[2][0], this->cube.faces[2].state[2][0],
                                           this->cube.faces[3].state[2][2]}) {
        return 2;
    }
        // check position 3
    else if (colorsToFind == std::set<int>{this->cube.faces[3].state[2][0], this->cube.faces[2].state[2][2],
                                           this->cube.faces[4].state[2][2]}) {
        return 3;
    }
        // check position 4
    else if (colorsToFind == std::set<int>{this->cube.faces[0].state[2][2], this->cube.faces[1].state[0][2],
                                           this->cube.faces[4].state[0][0]}) {
        return 4;
    }
        // check position 5
    else if (colorsToFind == std::set<int>{this->cube.faces[0].state[2][0], this->cube.faces[1].state[0][0],
                                           this->cube.faces[5].state[0][2]}) {
        return 5;
    }
        // check position 6
    else if (colorsToFind == std::set<int>{this->cube.faces[0].state[0][0], this->cube.faces[3].state[0][2],
                                           this->cube.faces[5].state[0][0]}) {
        return 6;
    }
        // check position 7
    else if (colorsToFind == std::set<int>{this->cube.faces[0].state[0][2], this->cube.faces[3].state[0][0],
                                           this->cube.faces[4].state[0][2]}) {
        return 7;
    } else {
        printf("\nWrong arguments passed to getCornerPos\n");
        return -1;
    }
}

void Solver::setSLEdges() {
    // solve the second layer edges
    int edgesSet = 0;
    int faceMoved = 0;

    // check how many edges are already set
    if ((this->cube.faces[1].getCenter() == this->cube.faces[1].state[1][2]) &&
        (this->cube.faces[4].getCenter() == this->cube.faces[4].state[1][0])) {
        edgesSet++;
    }

    if ((this->cube.faces[1].getCenter() == this->cube.faces[1].state[1][0]) &&
        (this->cube.faces[5].getCenter() == this->cube.faces[5].state[1][2])) {
        edgesSet++;
    }

    if ((this->cube.faces[4].getCenter() == this->cube.faces[4].state[1][2]) &&
        (this->cube.faces[3].getCenter() == this->cube.faces[3].state[1][0])) {
        edgesSet++;
    }

    if ((this->cube.faces[5].getCenter() == this->cube.faces[5].state[1][0]) &&
        (this->cube.faces[3].getCenter() == this->cube.faces[3].state[1][2])) {
        edgesSet++;
    }

    while (edgesSet < 4) {
        while (faceMoved < 4) {
            // check if front face top layer edge is valid
            if ((this->cube.faces[1].state[0][1] != 2) && (this->cube.faces[0].state[2][1] != 2)) {
                // valid edge present
                // find its corresponding face and set the edge, set faceMoved to 0 and increment edgesSet
                while (this->cube.faces[1].state[0][1] != this->cube.faces[1].getCenter()) {
                    // shift through the bottom two layers
                    this->cube.makeMove("d'");
                }

                // check which side to put the edge
                if (this->cube.faces[0].state[2][1] == this->cube.faces[5].getCenter()){
                    // move the edge to the left position
                    this->cube.makeMove({"U'", "L'", "U'", "L", "U", "y'", "R", "U", "R'", "U'", "y"});
                } else {
                    // move the edge to the right position
                    this->cube.makeMove({"U", "R", "U", "R'", "U'", "y", "L'", "U'", "L", "U", "y'"});
                }
                edgesSet++;
                if (edgesSet >= 4){
                    break;
                }
                faceMoved = 0;
            } else {
                this->cube.makeMove("U");
                faceMoved++;
            }
        }
        if (edgesSet < 4) {
            faceMoved = 0;
            // no valid edge on the top layer
            // find an unset edge in the middle layer and push it to top layer
            while ((this->cube.faces[1].getCenter() == this->cube.faces[1].state[1][2]) &&
                     (this->cube.faces[4].getCenter() == this->cube.faces[4].state[1][0])) {
                // cycle through the bottom two layers to find an unset front face right edge
                this->cube.makeMove("d");
            }
            // push the front face right edge to the top layer
            this->cube.makeMove({"U", "R", "U", "R'", "U'", "y", "L'", "U'", "L", "U", "y'"});
        }
    }
}

void Solver::setLLCorners() {
    // set the last layer corners

    // form the yellow cross
    switch (this->getLLPattern()) {
        case 1:
            // cross already solved
            // do nothing
            break;
        case 2:
            // L shape
            this->cube.makeMove({"f", "R", "U", "R'", "U'", "f'"});
            break;
        case 3:
            // line shape
            this->cube.makeMove({"F", "R", "U", "R'", "U'", "F'"});
            break;
        case 4:
            // dot shape
            this->cube.makeMove({"F", "R", "U", "R'", "U'", "F'"});
            this->cube.makeMove({"f", "R", "U", "R'", "U'", "f'"});
            break;
        default:
            printf("\nInvalid pattern\n");
    }


    // get edges into correct position
    int cornersSet = 0;

    for (int i = 0; i < 4; i++) {
        if (this->getCornersSet() == 4) {
            // all corners already in position
            cornersSet = 4;
            break;
        }
        else if (this->getCornersSet() == 2) {
            // check if diagonal or straight
            cornersSet == 2;
            break;
        }
        else {
            // less than 2 corners are set
            this->cube.makeMove("U");
        }
    }

    // at least two corners are set
    if (cornersSet == 2){
        // set all the corners
        switch (this->getSetCornerPosition()) {

        }
    }
}

int Solver::getLLPattern() {
    // get the pattern on the top layer

    if (this->cube.faces[0].state[1][0] == this->cube.faces[0].getCenter() &&
        this->cube.faces[0].state[0][1] == this->cube.faces[0].getCenter() &&
        this->cube.faces[0].state[1][2] == this->cube.faces[0].getCenter() &&
        this->cube.faces[0].state[2][1] == this->cube.faces[0].getCenter()) {
        // cross is already set
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        if (this->cube.faces[0].state[1][2] == this->cube.faces[0].getCenter() &&
            this->cube.faces[0].state[2][1] == this->cube.faces[0].getCenter()) {
            // L shape on the bottom right corner
            return 2;
        }
        else {
            // rotate the top face
            this->cube.makeMove("U");
        }
    }

    for (int i = 0; i < 2; i++) {
        if (this->cube.faces[0].state[1][0] == this->cube.faces[0].getCenter() &&
            this->cube.faces[0].state[1][1] == this->cube.faces[0].getCenter() &&
            this->cube.faces[0].state[1][2] == this->cube.faces[0].getCenter()) {
            // line shape
            return 3;
        } else {
            // rotate the top face
            this->cube.makeMove("U");
        }
    }

    // dot shape
    return 4;
    }

int Solver::getCornersSet() {
    // return the number of top layer corners in the correct position
    int cornersSet = 0;

    for (int i = 0; i < 4; i++) {
        std::set<int>colorsToFind{this->cube.faces[0].getCenter(), this->cube.faces[1].getCenter(),
                                  this->cube.faces[4].getCenter()};
        if (colorsToFind == std::set<int>{this->cube.faces[0].state[2][2], this->cube.faces[1].state[0][2],
                                          this->cube.faces[0].state[0][0]}) {
            // corner is set
            cornersSet++;
        }
        this->cube.makeMove("y");
    }

    return cornersSet;
}

int Solver::getSetCornerPosition() {
    // return the position where the corners are set
    //    1:
    //        X X 1
    //        X X X
    //        X X 1
    //
    //    2:
    //        X X X
    //        X X X
    //        2 X 2
    //
    //    3:
    //        3 X X
    //        X X X
    //        3 X X
    //
    //    4:
    //        4 X 4
    //        X X X
    //        X X X
    //
    //    5:
    //        5 X X
    //        X X X
    //        X X 5
    //
    //    6:
    //        X X 6
    //        X X X
    //        6 X X

    // check for position 1
    std::set<int>colorsToFind_1{this->cube.faces[0].getCenter(), this->cube.faces[1].getCenter(),
                                this->cube.faces[4].getCenter()};
    std::set<int>colorsToFind_2{this->cube.faces[0].getCenter(), this->cube.faces[3].getCenter(),
                                this->cube.faces[4].getCenter()};

    if (colorsToFind_1 == std::set<int>{this->cube.faces[0].state[2][0], this->cube.faces[1].state[1][2],
                                        this->cube.faces[4].state[0][0]} &&
        colorsToFind_2 == std::set<int>{this->cube.faces[0].state[0][2], this->cube.faces[3].state[0][0],
                                        this->cube.faces[4].state[0][2]}) {
        return 1;
    }



    // check for position 2
    colorsToFind_1 = {this->cube.faces[0].getCenter(), this->cube.faces[1].getCenter(), this->cube.faces[4].getCenter()};
    colorsToFind_2 = {this->cube.faces[0].getCenter(), this->cube.faces[1].getCenter(), this->cube.faces[4].getCenter()};

    if (colorsToFind_1 == std::set<int>{this->cube.faces[0].state[2][0], this->cube.faces[0].state[2][0],
                                        this->cube.faces[0].state[2][0]} &&
        colorsToFind_2 == std::set<int>{this->cube.faces[0].state[2][0], this->cube.faces[0].state[2][0],
                                        this->cube.faces[0].state[2][0]}) {
        return 1;
    }
}
