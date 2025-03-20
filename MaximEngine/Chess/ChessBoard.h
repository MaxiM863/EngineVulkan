#include<vector>

#include "ChessPartPion.h"
#include "ChessPartTour.h"

#include "CookbookSampleFramework.h"

#ifndef BOARD_SIZE
#define BOARD_SIZE 8
#endif

class ChessBoard
{
    public:

        ChessBoard()
        {             
            cases = new ChessPart*[BOARD_SIZE * BOARD_SIZE];

            for(int i = 0; i < 64; i++) cases[i] = nullptr;
            
            for(int c = 0; c < 2; c++)
            {
                // Pions
                for(int i = 0; i < BOARD_SIZE; i++)
                {

                    cases[i + BOARD_SIZE + c * BOARD_SIZE * 6] = new ChessPartPion(meshes);
                }
            }

            cases[0] = new ChessPartTour(meshes);
            cases[BOARD_SIZE-1] = new ChessPartTour(meshes);

        }

        ChessPart* getCaseBoard(int posX, int posY) 
        {
            return cases[posY * 8 + posX];
        }

        int getPosX(int num) { return num % 8; }
        int getPosY(int num) { return num / 8; }

    private:

        ChessPart** cases;

    public:
    
        ChessMesh meshes;
};