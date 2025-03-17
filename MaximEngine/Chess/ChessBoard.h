#include<vector>

#include "ChessCase.h"
#include "ChessPartPion.h"
#include "ChessPartTour.h"

#ifndef BOARD_SIZE
#define BOARD_SIZE 8
#endif

class ChessBoard
{
    public:

        ChessBoard()
        { 
            
            cases = new ChessCase*[BOARD_SIZE * BOARD_SIZE];
            
            ChessPart** parts = new ChessPart*[BOARD_SIZE * 4];

            for(int c = 0; c < 2; c++)
            {
                // Pions
                for(int i = 0; i < BOARD_SIZE; i++)
                {

                    ChessPartPion* tmpPion = new ChessPartPion();

                    cases[i + BOARD_SIZE + c * BOARD_SIZE * 6] = new ChessCase(tmpPion);
                }

                // Tours
                ChessPartTour* tmpTour = new ChessPartTour();

                cases[0] = new ChessCase(tmpTour);
                
                tmpTour = new ChessPartTour();

                cases[BOARD_SIZE-1] = new ChessCase(tmpTour);

                tmpTour = new ChessPartTour();

                cases[7*BOARD_SIZE] = new ChessCase(tmpTour);

                tmpTour = new ChessPartTour();

                cases[8*BOARD_SIZE-1] = new ChessCase(tmpTour);

                // Fou
                

            }
        }

    private:

        ChessCase** cases;
};