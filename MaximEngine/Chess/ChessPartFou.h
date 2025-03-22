#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartFou : public ChessPart
{
    public:

        ChessPartFou(ChessMesh meshList, int color){

            m_model = &meshList.m_Fou;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, ChessBoard board) override {
            
            std::vector<int> rep;

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(8+1) < 64)
                {
                    rep.push_back(position+(i+1)*(8+1));
                    if(board.getCaseBoard(board.getPosX(position+(i+1)*(8+1)), board.getPosY(position+(i+1)*(8+1))) != nullptr)
                    {
                        break;
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(8-1) < 64)
                {
                    rep.push_back(position+(i+1)*(8-1));
                    if(board.getCaseBoard(board.getPosX(position+(i+1)*(8-1)), board.getPosY(position+(i+1)*(8-1))) != nullptr)
                    {
                        break;
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8+1) >= 0)
                {
                    rep.push_back(position - (i+1)*(8+1) >= 0);
                    if(board.getCaseBoard(board.getPosX(position - (i+1)*(8+1) >= 0), board.getPosY(position - (i+1)*(8+1) >= 0)) != nullptr)
                    {
                        break;
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8-1) >= 0)
                {
                    rep.push_back(position - (i+1)*(8-1));
                    if(board.getCaseBoard(board.getPosX(position - (i+1)*(8-1)), board.getPosY(position - (i+1)*(8-1))) != nullptr)
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

        int bufferDraw = 4;
};