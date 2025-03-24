#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartKing : public ChessPart
{
    public:

    ChessPartKing(ChessMesh meshList, int color){

            m_model = &meshList.m_Roi;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, int color, bool isPion) override {
     
            std::vector<int> rep;

            if(position + (8 + 1) < 64) rep.push_back(position + (8 + 1) < 64);
            if(position + (8 - 1) < 64) rep.push_back(position + (8 - 1) < 64);
            
            if(position - (8 + 1) >= 0) rep.push_back(position - (8 + 1) < 64);
            if(position - (8 - 1) >= 0) rep.push_back(position - (8 - 1) < 64);
            
            if(position + (1) < 64) rep.push_back(position + (1) < 64);
            if(position - (1) >= 0) rep.push_back(position - (1) < 64);
            
            if(position + (8) < 64) rep.push_back(position + (8) < 64);
            if(position - (8) >= 0) rep.push_back(position - (8) >= 0);

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 2;
};