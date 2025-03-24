#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartCavalier : public ChessPart
{
    public:

        ChessPartCavalier(ChessMesh meshList, int color){

            m_model = &meshList.m_Cavalier;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, int color, bool isPion) override {
            
            std::vector<int> rep;

            if(position - (2 * 8 - 1) >= 0) rep.push_back(position-(2*8-1));
            if(position - (2 * 8 + 1) >= 0) rep.push_back(position-(2*8+1));

            if(position + (2 * 8 - 1) < 64) rep.push_back(position+(2*8-1));
            if(position + (2 * 8 + 1) < 64) rep.push_back(position+(2*8+1));

            if(position + (8 + 2) < 64) rep.push_back(position+(8+2));
            if(position + (8 - 2) < 64) rep.push_back(position+(8-2));

            if(position - (8 + 2) >= 0) rep.push_back(position-(8+2));
            if(position - (8 - 2) >= 0) rep.push_back(position-(8-2));

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 3;
};