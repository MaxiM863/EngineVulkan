#include<vector>
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
            
            cases = new ChessPartTour*[BOARD_SIZE * BOARD_SIZE];
            
            /*for(int c = 0; c < 2; c++)
            {
                // Pions
                for(int i = 0; i < BOARD_SIZE; i++)
                {

                    ChessPartPion* tmpPion = new ChessPartPion();

                    cases[i + BOARD_SIZE + c * BOARD_SIZE * 6] = new ChessCase(tmpPion);
                }
            }

            for(int c = 0; c < 2; c++)
            {
                // Pions
                for(int i = 0; i < BOARD_SIZE; i++)
                {

                    ChessPartTour* tmpTour = new ChessPartTour();

                    cases[i + c * BOARD_SIZE * 7] = new ChessCase(tmpTour);
                }
            }*/

            for(int i = 0; i < 64; i++)
            {
                
                cases[i] = new ChessPartTour();
            }                       
        }

        std::vector<VulkanCookbook::Mesh>* getModelsMesh()
        {
            std::vector<VulkanCookbook::Mesh> data;

            for(int i = 0; i < 64; i++)
            {
                data.push_back(cases[i]->m_model);
            }

            return &data;
        }

    private:

        ChessPartTour** cases;
};