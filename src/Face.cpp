//
// Created by sumeet on 12/04/20.
//

#include "Face.hpp"

// Method to get the center of the face
int Face::getCenter(){
    return this->state[1][1];
}

// Method to set all the tiles of the face
void Face::setAllTiles(int num){
    for(auto & i : this->state){
        for(int & j : i){
            j = num;
        }
    }
}

void Face::rotateClockwise(){
    // Transpose the face state matrix and then swap the first and last column
    this->transposeState();

    // Swap the first and last column
    this->swapColumn(0, 2);
}

void Face::rotateAntiClockwise(){
    // Transpose the face state matrix and then swap the first and last row
    this->transposeState();

    // Swap the first and last row
    this->swapRow(0, 2);
}

void Face::swapStateElement(int a, int b, int c, int d){
    // Swap state[a][b] and state[c][d]

    this->state[a][b] = this->state[a][b] + this->state[c][d];
    this->state[c][d] = this->state[a][b] - this->state[c][d];
    this->state[a][b] = this->state[a][b] - this->state[c][d];
}

void Face::transposeState(){
    // Swap [0][1] and [1][0]
    this->swapStateElement(0, 1, 1, 0);

    // Swap [0][2] and [2][0]
    this->swapStateElement(0, 2, 2, 0);

    // Swap [1][2] and [2][1]
    this->swapStateElement(1, 2, 2, 1);
}

void Face::swapRow(int a, int b){
    // [a][0:2] <-> [b][0:2]
    for (int i = 0; i < 3; i++){
        this->swapStateElement(a, i, b, i);
    }
}

void Face::swapColumn(int a, int b){
    // [0:2][a] <-> [0:2][b]
    for (int i = 0; i < 3; i++){
        this->swapStateElement(i, a, i, b);
    }
}