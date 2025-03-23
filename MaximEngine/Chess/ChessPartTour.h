#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartTour : public ChessPart
{
    public:

        ChessPartTour(ChessMesh meshList, int color){

            m_model = &meshList.m_Tour;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, ChessBoard board) override {
            
            std::vector<int> rep;

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8) >= 0)
                {
                    rep.push_back(position - (i+1)*(8));
                    if(board.getCaseBoard(board.getPosX(position - (i+1)*(8)), board.getPosY(position - (i+1)*(8))) != nullptr)
                    {
                        break;
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(1) >= 0)
                {
                    rep.push_back(position - (i+1)*(1));
                    if(board.getCaseBoard(board.getPosX(position - (i+1)*(1)), board.getPosY(position - (i+1)*(1))) != nullptr)
                    {
                        break;
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(8) >= 0)
                {
                    rep.push_back(position + (i+1)*(8));
                    if(board.getCaseBoard(board.getPosX(position + (i+1)*(8)), board.getPosY(position + (i+1)*(8))) != nullptr)
                    {
                        break;
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(1) >= 0)
                {
                    rep.push_back(position + (i+1)*(1));
                    if(board.getCaseBoard(board.getPosX(position + (i+1)*(1)), board.getPosY(position + (i+1)*(1))) != nullptr)
                    {
                        break;
                    }
                }
            }

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 1;
};