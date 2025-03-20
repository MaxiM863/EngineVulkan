#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartCavalier : public ChessPart
{
    public:

        ChessPartCavalier(ChessMesh meshList, int color){

            m_model = &meshList.m_Cavalier;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible() override {
            
            return std::vector<int>();
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 3;
};