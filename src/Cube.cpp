//
// Created by sumeet on 12/04/20.
//

#include "Cube.hpp"

//TODO: 1. Allow user to provide multiple moves at once(overload makeMove)
//  2. Allow user to store the state of the cube
//  3. Allow the user to check if two cube states are equal
//  3. Allow the user to query if cube is solved

Cube::Cube():faces(6){
    // Initialize the cube's faces
    for(int i = 0; i < 6; i++){
        this->faces[i].setAllTiles(i);
    }
    this->randomizeCube();
}

void Cube::printCube(bool pretty, bool is256ColorSupported){
// The cube will be printed in the following format:
//
//          9 8 7
//          6 R 4
//          3 2 1
//          - - -
//  7 4 1 | 3 6 9 | 3 6 9 | 3 6 9
//  8 B 2 | 2 U 8 | 2 F 8 | 2 D 8
//  9 6 3 | 1 4 7 | 1 4 7 | 1 4 7
//          - - -
//          1 2 3
//          4 L 6
//          7 8 9
//
// Here 1 represents the top left corner of the face when the face is oriented towards the user

    printf("\n-------------------------------------------\n");

    // Print the R face

    // Print the R face elements
    for (int i = 2; i >= 0; i--){
        printf("           ");
        for (int j = 2; j >= 0; j--){
            if(!pretty){
                // Non pretty printing
                printf("%d ", this->faces[4].state[i][j]);
            }
            else{
                // Pretty printing
                Cube::prettyPrint(this->faces[4].state[i][j], is256ColorSupported);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("          ");
    printf("----------\n");






    // Print the B, U, F and D faces

    // Perform clockwise rotation on face B
    this->faces[3].rotateClockwise();

    // Perform anticlockwise rotation on face U
    this->faces[0].rotateAntiClockwise();

    // Perform anticlockwise rotation on face F
    this->faces[1].rotateAntiClockwise();

    // Perform anticlockwise rotation on face D
    this->faces[2].rotateAntiClockwise();

    int idx = 0;

    // Print the matrix
    for (int i = 0; i < 3; i++){ // NOLINT(modernize-loop-convert)
        for (int j = -1; j < 3; j++){
            for (int k = 0; k < 3; k ++){

                // Set correct face indexing
                if(j < 0){
                    idx = 3;
                }else{
                    idx = j;
                }

                if(!pretty){
                    // Non pretty printing
                    printf("%d ", this->faces[idx].state[i][k]);
                }
                else{
                    // Pretty printing
                    Cube::prettyPrint(this->faces[idx].state[i][k], is256ColorSupported);
                }
                printf(" ");
            }
            if (j < 2){
                printf("| ");
            }
        }
        printf("\n");
    }

    // Restore face B
    this->faces[3].rotateAntiClockwise();

    // Restore face U
    this->faces[0].rotateClockwise();

    // Restore face F
    this->faces[1].rotateClockwise();

    // Restore face D
    this->faces[2].rotateClockwise();






    // Print face L

    printf("          ");
    printf("----------\n");

    for (auto & i : this->faces[5].state){
        printf("           ");
        for (int j : i){
            if(!pretty){
                // Non pretty printing
                printf("%d ", j);
            }
            else{
                // Pretty printing
                Cube::prettyPrint(j, is256ColorSupported);
            }
            printf(" ");
        }
        printf("\n");
    }

    printf("\n-------------------------------------------\n");

}

void Cube::prettyPrint(int num, bool is256ColorSupported){
    // Pretty print colors instead of numbers

    std::string colorSpec;

    if (!is256ColorSupported){
        // xTerm 256 colors not supported
        switch (num)
        {
            case 0:
                // White
                colorSpec = "47m";
                break;

            case 1:
                // Blue
                colorSpec = "44m";
                break;

            case 2:
                // Yellow
                colorSpec = "43m";
                break;

            case 3:
                // Green
                colorSpec = "42m";
                break;

            case 4:
                // Orange is not available in non 256 colors. Using cyan.
                colorSpec = "46m";
                break;

            default:
                // Red
                colorSpec = "41m";
                break;
        }
    }
    else{
        // xTerm 256 colors supported
        switch (num)
        {
            case 0:
                // White
                colorSpec = "48;5;15m";
                break;

            case 1:
                // Blue
                colorSpec = "48;5;32m";
                break;

            case 2:
                // Yellow
                colorSpec = "48;5;226m";
                break;

            case 3:
                // Green
                colorSpec = "48;5;28m";
                break;

            case 4:
                // Orange
                colorSpec = "48;5;202m";
                break;

            default:
                // Red
                colorSpec = "48;5;196m";
                break;
        }
    }
    printf("\033[4;30;%s  \033[0m", colorSpec.c_str());
}

void Cube::randomizeCube(){
    printf("randomizing\n");
};

void Cube::makeMove(const std::string& move){
    if ("U" == move){
        // Perform the move U

        // Top face clockwise 90deg
        this->faces[0].rotateClockwise();

        // Swap first row of front face with top row of left face
        this->swapRowCols(1, 5, 0, 0);

        // Swap first row of front face with the top row of the back face
        this->swapRowCols(1, 3, 0, 0);

        // Swap first row of front face with the top row of right face
        this->swapRowCols(1, 4, 0, 0);
    }
    else if ("R" == move){
        // Perform the move R

        // Right face clockwise 90deg
        this->faces[4].rotateClockwise();

        // Swap last column of top face with the first column of back face with inversion
        this->swapRowCols(0, 3, 5, 3, true);

        // Swap the last column of the top face with the last column of the down face
        this->swapRowCols(0, 2, 5, 5);

        // Swap the last column of the top face with the last column of the front face
        this->swapRowCols(0, 1, 5, 5);
    }
    else if ("F" == move){
        // Perform the move F

        // Front face clockwise 90deg
        this->faces[1].rotateClockwise();

        // Swap the last row of top face with the first column of the right face
        this->swapRowCols(0, 4, 2, 3);

        // Swap the last row of the top face with the first row of the bottom face with inversion
        this->swapRowCols(0, 2, 2, 0, true);

        // Swap the last row of the top face with the last column of the left face with inversion
        this->swapRowCols(0, 5, 2, 5, true);
    }
    else if ("D" == move){
        // Perform the move D

        // Down face clockwise 90deg
        this->faces[2].rotateClockwise();

        // Swap front face last row with right face last row
        this->swapRowCols(1, 4, 2, 2);

        // Swap fron face last row with back face last row
        this->swapRowCols(1, 3, 2, 2);

        // Swap front face last row with left face last row
        this->swapRowCols(1, 5, 2, 2);
    }
    else if ("L" == move){
        // Perform the move L

        // Left face clockwise 90deg
        this->faces[5].rotateClockwise();

        // Swap top face first column and front face first column
        this->swapRowCols(0, 1, 3, 3);

        // Swap top face first column with bottom face first column
        this->swapRowCols(0, 2, 3, 3);

        // Swap the top face first column with back face last column with inversion
        this->swapRowCols(0, 3, 3, 5, true);
    }
    else if("B" == move){
        // Perform the B move

        // Back face clockwise 90deg
        this->faces[3].rotateClockwise();

        // Swap top face first row with left face first column with inversion
        this->swapRowCols(0, 5, 0, 3, true);

        // Swap top face first row with down face last row
        this->swapRowCols(0, 2, 0, 2, true);

        // Swap top face first row with right face last column with inversion
        this->swapRowCols(0, 4, 0, 5);
    }
    else if ("U'" == move){
        // Perform the U' move

        // Top face anticlockwise 90deg
        this->faces[0].rotateAntiClockwise();

        // Swap the front face first row with the right face first row
        this->swapRowCols(1, 4, 0, 0);

        // Swap the front face firt row with the back face first row
        this->swapRowCols(1, 3, 0, 0);

        // Swap the front face first row with the left face first row
        this->swapRowCols(1, 5, 0, 0);
    }
    else if("R'" == move){
        // Perform the R' move

        // Right face anticlockwise 90deg
        this->faces[4].rotateAntiClockwise();

        // Swap last column of top face with the last column of front face
        this->swapRowCols(0, 1, 5, 5);

        // Swap the last column of the top face with the last column of the down face
        this->swapRowCols(0, 2, 5, 5);

        // Swap the last column of the top face with the first column of the back face
        this->swapRowCols(0, 3, 5, 3, true);
    }
    else if ("F'" == move){
        // Perform the F' move

        // Front face anticlockwise 90deg
        this->faces[1].rotateAntiClockwise();

        // Swap top face last row with left face last column with inversion
        this->swapRowCols(0, 5, 2, 5, true);

        // Swap top face last row with bottom face first row
        this->swapRowCols(0, 2, 2, 0, true);

        // Swap top face last row with right face first column with inversion
        this->swapRowCols(0, 4, 2, 3);
    }
    else if ("D'" == move){
        // Perform the D' move

        // Down face anticlockwise 90deg
        this->faces[2].rotateAntiClockwise();

        // Swap front face last row and left face last row
        this->swapRowCols(1, 5, 2, 2);

        // Swap front face last row and back face last row
        this->swapRowCols(1, 3, 2, 2);

        // Swap front face last row and right face last row
        this->swapRowCols(1, 4, 2, 2);
    }
    else if ("L'" == move){
        // Perform the L' move

        // Swap left face anticlockwise 90deg
        this->faces[5].rotateAntiClockwise();

        // Swap top face first column and back face last column with inversion
        this->swapRowCols(0, 3, 3, 5, true);

        // Swap top face first column and bottom face first column
        this->swapRowCols(0, 2, 3, 3);

        // Swap top face first column and front face first column
        this->swapRowCols(0, 1, 3, 3);
    }
    else if ("B'" == move){
        // Perform the B' move

        // Back face anticlckwise 90 deg
        this->faces[3].rotateAntiClockwise();

        // Swap top face first row and right face last column
        this->swapRowCols(0, 4, 0, 5);

        // Swap top face first row and bottom face last row with inversion
        this->swapRowCols(0, 2, 0, 2, true);

        // Swap top face first row and left face first column with inversion
        this->swapRowCols(0, 5, 0, 3, true);
    }else if("U2" == move){
        // Perform move U2

        // Perform move U twice
        this->makeMove("U");
        this->makeMove("U");
    }
    else if("R2" == move){
        // Perform move R2

        // Perform move R twice
        this->makeMove("R");
        this->makeMove("R");
    }
    else if("F2" == move){
        // Perform move F2

        // Perform move F twice
        this->makeMove("F");
        this->makeMove("F");
    }else if("D2" == move){
        // Perform move D2

        // Perform move D twice
        this->makeMove("D");
        this->makeMove("D");
    }
    else if("L2" == move){
        // Perform move L2

        // Perform move L twice
        this->makeMove("L");
        this->makeMove("L");
    }
    else if("B2" == move){
        // Perform move B2

        // Perform move B twice
        this->makeMove("B");
        this->makeMove("B");
    }
    else if ("M" == move){
        // Perform the M move

        // Swap top face middle column and front face middle column
        this->swapRowCols(0, 1, 4, 4);

        // Swap top face middle colum and down face middle column
        this->swapRowCols(0, 2, 4, 4);

        // Swap top face middle column and back face middle column with inversion
        this->swapRowCols(0, 3, 4, 4, true);
    }
    else if ("M'" == move){
        // Perform the M' move

        // Swap bottom face middle column and front face middle column
        this->swapRowCols(2, 1, 4, 4);

        // Swap bottom face middle column and top face middle column
        this->swapRowCols(2, 0, 4, 4);

        // Swap bottom face middle column and back face middle column with inversion
        this->swapRowCols(2, 3, 4, 4, true);
    }
    else if ("E" == move){
        // Perform the move E

        // Swap the front face middle row and the right face middle row
        this->swapRowCols(1, 4, 1, 1);

        // Swap the front face middle row and the back face middle row
        this->swapRowCols(1, 3, 1, 1);

        // Swap the front face middle row and the left face middle row
        this->swapRowCols(1, 5, 1, 1);
    }
    else if ("E'" == move){
        // Perform the E' move

        // Swap the front face middle row to the left face middle row
        this->swapRowCols(1, 5, 1, 1);

        // Swap the front face middle row to the back face middle row
        this->swapRowCols(1, 3, 1, 1);

        // Swap the front face middle row to the right face middle row
        this->swapRowCols(1, 4, 1, 1);
    }
    else if ("S" == move){
        // Perform the move S

        // Swap top face middle row and right face middle column
        this->swapRowCols(0, 4, 1, 4);

        // Swap the top face middle row and bottom face middle row with inversion
        this->swapRowCols(0, 2, 1, 1, true);

        // Swap the top face middle row and left face middle column with inversion
        this->swapRowCols(0, 5, 1, 4, true);
    }
    else if ("S'" == move){
        // Perform the move S'

        // Swap the top face middle row and left face middle column with inversion
        this->swapRowCols(0, 5, 1, 4, true);

        // Swap the top face middle row and bottom face middle row
        this->swapRowCols(0, 2, 1, 1, true);

        // Swap the top face middle row and right face middle column with inversion
        this->swapRowCols(0, 4, 1, 4);
    }
    else if ("u" == move){
        // Perform move u

        // Perform move U and E'
        this->makeMove("U");
        this->makeMove("E'");
    }
    else if ("u'" == move){
        // Perform move u'

        // Perform move U' and E
        this->makeMove("U'");
        this->makeMove("E");
    }
    else if ("r" == move){
        // Perform move r

        // Perform move R and M'
        this->makeMove("R");
        this->makeMove("M'");
    }
    else if ("r'" == move){
        // Perform move r'

        // Perform move R' and M
        this->makeMove("R'");
        this->makeMove("M");
    }
    else if ("f" == move){
        // Perform move f

        // Perform move F and S
        this->makeMove("F");
        this->makeMove("S");
    }
    else if ("f'" == move){
        // Perform move f'

        // Perform move F' and S'
        this->makeMove("F'");
        this->makeMove("S'");
    }
    else if ("d" == move){
        // Perform move d

        // Perform move D and E
        this->makeMove("D");
        this->makeMove("E");
    }
    else if ("d'" == move){
        // Perform move d'

        // Perform move D' and E'
        this->makeMove("D'");
        this->makeMove("E'");
    }
    else if ("l" == move){
        // Perform move l

        // Perform move L and M
        this->makeMove("L");
        this->makeMove("M");
    }
    else if ("l'" == move){
        // Perform move l'

        // Perform move L' and M'
        this->makeMove("L'");
        this->makeMove("M'");
    }
    else if ("b" == move){
        // Perform move b

        // Perform move B and S'
        this->makeMove("B");
        this->makeMove("S'");
    }
    else if ("b'" == move){
        // Perform move b'

        // Perform move B' and S
        this->makeMove("B'");
        this->makeMove("S");
    }
    else if ("x" == move){
        // Perform move x

        // Perform the moves R, L' and M'
        this->makeMove("R");
        this->makeMove("L'");
        this->makeMove("M'");
    }
    else if ("x'" == move){
        // Perform move x'

        // Perform the moves R', L and M
        this->makeMove("R'");
        this->makeMove("L");
        this->makeMove("M");
    }
    else if ("y" == move){
        // Perform the move y

        // Perform the moves U, D' and E'
        this->makeMove("U");
        this->makeMove("D'");
        this->makeMove("E'");
    }
    else if ("y'" == move){
        // Perform the move y'

        // Perform the moves U', D and E
        this->makeMove("U'");
        this->makeMove("D");
        this->makeMove("E");
    }
    else if ("z" == move){
        // Perform the move z

        // Perform the moves F, S and B'
        this->makeMove("F");
        this->makeMove("S");
        this->makeMove("B'");
    }
    else if ("z'" == move){
        // Perform the move z'

        // Perform the moves F', S' and B
        this->makeMove("F'");
        this->makeMove("S'");
        this->makeMove("B");
    }
    else{
        printf("\nInvalid Move requested!\n");
    }

}

void Cube::swapRowCols(int f1, int f2, int rowCol_1, int rowCol_2, bool invertOrder){
    // Generic function to swap rows and columns of the cube faces

    // f1 : face 1
    // f2 : face 2
    // rowCol_1 :
    // 0 : first row of f1
    // 1 : second row of f1
    // 2 : third row of f1
    // 3 : first column of f1
    // 4 : second column of f1
    // 5 : third column of f1
    // rowCol_2 :
    // 0 : first row of f2
    // 1 : second row of f2
    // 2 : third row of f2
    // 3 : first column of f2
    // 4 : second column of f2
    // 5 : third column of f2
    // invertOrder : reverse the order of the row or col from f1 before swaping it to face f2

    int rowIdx1, colIdx1, rowIdx2, colIdx2, idx;

    for (int i = 0; i < 3; i++){

        // Check if order needs to be inverted
        if (invertOrder){
            idx = 2 - i;
        }
        else{
            idx = i;
        }

        if (rowCol_1 < 3){
            // Row needs to be swapped
            rowIdx1 = rowCol_1;
            colIdx1 = idx;
        }
        else{
            // Column needs to be swaped
            rowIdx1 = idx;
            colIdx1 = rowCol_1 - 3;
        }

        if (rowCol_2 < 3){
            // Row needs to be swapped
            rowIdx2 = rowCol_2;
            colIdx2 = i;
        }
        else{
            // Column needs to be swapped
            rowIdx2 = i;
            colIdx2 = rowCol_2 - 3;
        }

        // Perform swap
        this->faces[f1].state[rowIdx1][colIdx1] = this->faces[f1].state[rowIdx1][colIdx1] + this->faces[f2].state[rowIdx2][colIdx2];
        this->faces[f2].state[rowIdx2][colIdx2] = this->faces[f1].state[rowIdx1][colIdx1] - this->faces[f2].state[rowIdx2][colIdx2];
        this->faces[f1].state[rowIdx1][colIdx1] = this->faces[f1].state[rowIdx1][colIdx1] - this->faces[f2].state[rowIdx2][colIdx2];
    }
}

