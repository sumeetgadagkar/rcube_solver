#include "src/Cube.hpp"
#include <random>
#include <chrono>

int main(int argc, char** argv){

    Cube myCube;
    std::vector<std::string> movesToMake;
    int numMoves = 8;

    // Set up RNG
    unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);


    // Randomly pick 10 moves from available moves
    for (int i = 0; i < numMoves; i++){
        auto idx = rng() % validMoves.size();
        movesToMake.push_back(validMoves[idx]);
    }

    // print the chosen moves
    for (const auto& move : movesToMake){
        printf("%s ", move.c_str());
    }

    // make the moves
    for (const auto& move : movesToMake){
        myCube.makeMove(move);
    }

    // print the cube
    myCube.printCube(true, true);
    return 0;
}