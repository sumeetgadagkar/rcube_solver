//
// Created by sumeet on 12/04/20.
//

#ifndef RCUBE_SOLVER_FACE_HPP
#define RCUBE_SOLVER_FACE_HPP

class Face{
public:
    // Properties
    int state[3][3];

    // Methods
    int getCenter();
    void setAllTiles(int num);
    void rotateClockwise();
    void rotateAntiClockwise();
    void swapStateElement(int a, int b, int c, int d);
    void transposeState();
    void swapRow(int a, int b);
    void swapColumn(int a, int b);
};


#endif //RCUBE_SOLVER_FACE_HPP
