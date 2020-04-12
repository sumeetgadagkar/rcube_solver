#include "src/Cube.hpp"
#include <time.h>

int main(int argc, char** argv){
    Cube myCube;
    std::string movesAvailable[] = {"U", "R", "F", "D", "L", "B"};
    std::vector<std::string> movesToMake;
    std::string::iterator it;
    int numMoves = 8;

    srand(time(0));

    // Randomly pick 10 moves from available moves
    for (int i = 0; i < numMoves; i++){
        int idx = rand() % sizeof(movesAvailable)/sizeof(movesAvailable[0]);
        movesToMake.push_back(movesAvailable[idx]);
    }

    // print the chosen moves
    for (auto move : movesToMake){
        printf("%s ", move.c_str());
    }

    // make the moves
    for (auto move : movesToMake){
        myCube.makeMove(move);
    }

    // print the cube
    myCube.printCube(true, true);

    myCube.makeMove("x'");
    myCube.printCube(true, true);
    return 0;
}