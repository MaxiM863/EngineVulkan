#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartKing : public ChessPart
{
    public:

    ChessPartKing(ChessMesh meshList, int color){

            m_model = &meshList.m_Roi;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, std::vector<ChessPart*> parts, int color, bool isPion, int& mange) override {
     
            std::vector<int> rep;

            if(position + (8 + 1) < 64 && (isOpponant(position + (8 + 1), color, parts) || !isOccupied(position + (8 + 1), occupe))) rep.push_back(position + (8 + 1) < 64);
            if(position + (8 - 1) < 64 && (isOpponant(position + (8 - 1), color, parts) || !isOccupied(position + (8 - 1), occupe))) rep.push_back(position + (8 - 1) < 64);
            
            if(position - (8 + 1) >= 0 && (isOpponant(position - (8 + 1), color, parts) || !isOccupied(position - (8 + 1), occupe))) rep.push_back(position - (8 + 1) < 64);
            if(position - (8 - 1) >= 0 && (isOpponant(position - (8 - 1), color, parts) || !isOccupied(position - (8 - 1), occupe))) rep.push_back(position - (8 - 1) < 64);
            
            if(position + (1) < 64 && (isOpponant(position + (1), color, parts) || !isOccupied(position + (1), occupe))) rep.push_back(position + (1) < 64);
            if(position - (1) >= 0 && (isOpponant(position - (1), color, parts) || !isOccupied(position - (1), occupe))) rep.push_back(position - (1) < 64);
            
            if(position + (8) < 64 && (isOpponant(position + (8), color, parts) || !isOccupied(position + (8), occupe))) rep.push_back(position + (8) < 64);
            if(position - (8) >= 0 && (isOpponant(position - (8), color, parts) || !isOccupied(position - (8), occupe))) rep.push_back(position - (8) >= 0);

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 2;
};