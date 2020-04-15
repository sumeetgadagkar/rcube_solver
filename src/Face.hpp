/*
 * Declaration of Face class to represent a single face of a rubik's cube
 * Author : zoroppz
 */

#ifndef RCUBE_SOLVER_FACE_HPP
#define RCUBE_SOLVER_FACE_HPP

class Face{

public:
    virtual ~Face();

public:
    int state[3][3]; // State to store color grid information
        // [0][0] - top left corner
        // [0][1] - top row middle
        // [0][2] - top row right corner
        // [1][0] - middle row left
        // ...

    int getCenter(); // return color of the center tile of the face
        // 0 - white
        // 1 - blue
        // 2 - yellow
        // 3 - green
        // 4 - orange
        // 5 - red

    void setAllTiles(int num); // set all the tiles of the face to the value provided

    void rotateClockwise(); // rotate the face clockwise(top left corner -> top right corner)

    void rotateAntiClockwise(); // rotate the face counter clockwise (top right corner -> top left corner)

private:
    void swapStateElement(int a, int b, int c, int d); // swap element [a][b] with [c][d]

    void transposeState(); // transpose the face state matrix

    void swapRow(int a, int b); // swap row a and b

    void swapColumn(int a, int b); // swap column a and b
};


#endif //RCUBE_SOLVER_FACE_HPP
