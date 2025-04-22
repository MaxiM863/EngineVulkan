#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartCavalier : public ChessPart
{
    public:

        ChessPartCavalier(ChessMesh meshList, int color){

            m_model = &meshList.m_Cavalier;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, std::vector<ChessPart*> parts, int color, bool isPion, int& mange) override {
            
            std::vector<int> rep;

            if(position - (2 * 8 - 1) >= 0 && (isOpponant(position - (2*8-1), color, parts) || !isOccupied(position - (2*8-1), occupe)) && (position % 8 != 0 && position / 8 >= 2)) rep.push_back(position-(2*8-1));
            if(position - (2 * 8 + 1) >= 0 && (isOpponant(position - (2*8+1), color, parts) || !isOccupied(position - (2*8+1), occupe)) && position % 8 != 7 && position / 8 >= 2) rep.push_back(position-(2*8+1));

            if(position + (2 * 8 - 1) < 64 && (isOpponant(position + (2*8-1), color, parts) || !isOccupied(position + (2*8-1), occupe)) && position % 8 != 0 && position / 8 <= 5) rep.push_back(position+(2*8-1));
            if(position + (2 * 8 + 1) < 64 && (isOpponant(position + (2*8+1), color, parts) || !isOccupied(position + (2*8+1), occupe)) && position % 8 != 7 && position / 8 <= 5) rep.push_back(position+(2*8+1));

            if(position + (8 + 2) < 64 && (isOpponant(position + (8+2), color, parts) || !isOccupied(position + (8+2), occupe)) && position % 8 <= 5 && position / 8 <= 6) rep.push_back(position+(8+2));
            if(position + (8 - 2) < 64 && (isOpponant(position + (8-2), color, parts) || !isOccupied(position + (8-2), occupe)) && position % 8 >= 2 && position / 8 <= 6) rep.push_back(position+(8-2));

            if(position - (8 + 2) >= 0 && (isOpponant(position - (8+2), color, parts) || !isOccupied(position - (8+2), occupe)) && position % 8 <= 5 && position / 8 >= 1) rep.push_back(position-(8+2));
            if(position - (8 - 2) >= 0 && (isOpponant(position - (8-2), color, parts) || !isOccupied(position - (8-2), occupe)) && position % 8 >= 2 && position / 8 >= 1) rep.push_back(position-(8-2));

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 3;
};