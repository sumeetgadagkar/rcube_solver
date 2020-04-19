/*
 *  Definition of Face class
 *  Author : zoroppz
 */

#include "Face.hpp"


int Face::getCenter() {
    return this->state[1][1];
}

void Face::setAllTiles(int num) {
    // iterate over face rows
    for (auto &i : this->state) {
        // iterate over columns
        for (int &j : i) {
            j = num;
        }
    }
}

void Face::rotateClockwise() {
    // transpose the face state matrix and then swap the first and last column
    this->transposeState();

    // swap the first and last column
    this->swapColumn(0, 2);
}

void Face::rotateAntiClockwise() {
    // transpose the face state matrix and then swap the first and last row
    this->transposeState();

    // swap the first and last row
    this->swapRow(0, 2);
}

void Face::swapStateElement(int a, int b, int c, int d) {
    // swap state[a][b] and state[c][d]

    this->state[a][b] = this->state[a][b] + this->state[c][d];
    this->state[c][d] = this->state[a][b] - this->state[c][d];
    this->state[a][b] = this->state[a][b] - this->state[c][d];
}

void Face::transposeState() {
    // swap [0][1] and [1][0]
    this->swapStateElement(0, 1, 1, 0);

    // swap [0][2] and [2][0]
    this->swapStateElement(0, 2, 2, 0);

    // swap [1][2] and [2][1]
    this->swapStateElement(1, 2, 2, 1);
}

void Face::swapRow(int a, int b) {
    // [a][0:2] <-> [b][0:2]
    for (int i = 0; i < 3; i++) {
        this->swapStateElement(a, i, b, i);
    }
}

void Face::swapColumn(int a, int b) {
    // [0:2][a] <-> [0:2][b]
    for (int i = 0; i < 3; i++) {
        this->swapStateElement(i, a, i, b);
    }
}

Face::~Face() = default;
