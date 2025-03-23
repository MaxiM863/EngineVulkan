#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartPion : public ChessPart
{
    public:

        ChessPartPion(ChessMesh meshList, int color){

            m_model = &meshList.m_Pion;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, ChessBoard board) override {
            
            std::vector<int> rep;

            int switchColor = 1;

            if(board.getCaseBoard(board.getPosX(position), board.getPosY(position))->colorPart == 1) switchColor = -1;
            
            if(position + switchColor * 8 < 64 && position + switchColor * 8 >= 0 && board.getCaseBoard(board.getPosX(position + switchColor * 8), board.getPosY(position + switchColor * 8)) == nullptr)
            {
                rep.push_back(position + switchColor * 8);
            }

            if(position/8 == 6 || position/8 == 1)
            {
                if(position + switchColor * 16 < 64 && position + switchColor * 16 >= 0 && board.getCaseBoard(board.getPosX(position + switchColor * 16), board.getPosY(position + switchColor * 16)) == nullptr)
                {
                    rep.push_back(position + switchColor * 16);
                }
            }

            if(position%8 == 7)
            {
                if(board.getCaseBoard(board.getPosX(position) - 1 * switchColor, board.getPosY(position)) != nullptr)
                {
                    rep.push_back(position - switchColor * (1));
                }
            }
            else if(position%8 == 0)
            {
                if(board.getCaseBoard(board.getPosX(position) + 1 * switchColor, board.getPosY(position)) != nullptr)
                {
                    rep.push_back(position + switchColor * (1));
                }
            }
            else
            {
                if(board.getCaseBoard(board.getPosX(position) + 1 * switchColor, board.getPosY(position)) != nullptr)
                {
                    rep.push_back(position + switchColor * (1));
                }
                if(board.getCaseBoard(board.getPosX(position) - 1 * switchColor, board.getPosY(position)) != nullptr)
                {
                    rep.push_back(position - switchColor * (1));
                }
            }           

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 0;
};