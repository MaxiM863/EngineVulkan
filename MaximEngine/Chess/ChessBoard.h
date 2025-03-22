#include<vector>

#include "ChessPartPion.h"
#include "ChessPartTour.h"
#include "ChessPartKing"
#include "ChessPartQueen.h"
#include "ChessPartCavalier.h"
#include "ChessPartFou.h"
#include "ChessPartCase.h"

#include "CookbookSampleFramework.h"

#ifndef BOARD_SIZE
#define BOARD_SIZE 8
#endif

class ChessBoard
{
    public:

        ChessBoard()
        {             
            cases = new ChessPart*[2 * BOARD_SIZE * BOARD_SIZE];

            for(int i = 0; i < 64; i++) cases[i] = nullptr;
            
            for(int c = 0; c < 2; c++)
            {
                // Pions
                for(int i = 0; i < BOARD_SIZE; i++)
                {

                    cases[i + BOARD_SIZE + c * BOARD_SIZE * 5] = new ChessPartPion(meshes, c);
                }
            }

            cases[0] = new ChessPartTour(meshes,0);
            cases[BOARD_SIZE-1] = new ChessPartTour(meshes,0);
            cases[7*BOARD_SIZE] = new ChessPartTour(meshes,1);
            cases[BOARD_SIZE*BOARD_SIZE-1] = new ChessPartTour(meshes,1);

            cases[1] = new ChessPartCavalier(meshes,0);
            cases[BOARD_SIZE-2] = new ChessPartCavalier(meshes,0);
            cases[7*BOARD_SIZE+1] = new ChessPartCavalier(meshes,1);
            cases[BOARD_SIZE*BOARD_SIZE-2] = new ChessPartCavalier(meshes,1);

            cases[2] = new ChessPartFou(meshes,0);
            cases[BOARD_SIZE-3] = new ChessPartFou(meshes,0);
            cases[7*BOARD_SIZE+2] = new ChessPartFou(meshes,1);
            cases[BOARD_SIZE*BOARD_SIZE-3] = new ChessPartFou(meshes,1);

            cases[3] = new ChessPartKing(meshes, 0);
            cases[7*BOARD_SIZE+3] = new ChessPartKing(meshes, 1);

            cases[4] = new ChessPartQueen(meshes, 0);
            cases[7*BOARD_SIZE+4] = new ChessPartQueen(meshes, 1);

            squares = new ChessPart*[2];

            squares[0] = new ChessPartCase(meshes, 0);
            squares[1] = new ChessPartCase(meshes, 1);

        }

        ChessPart* getCaseBoard(int posX, int posY) 
        {
            return cases[posY * 8 + posX];
        }

        int getPosX(int num) { return num % 8; }
        int getPosY(int num) { return num / 8; }

    private:

        ChessPart** cases;
        ChessPart** squares;

    public:

        ChessMesh meshes;
};