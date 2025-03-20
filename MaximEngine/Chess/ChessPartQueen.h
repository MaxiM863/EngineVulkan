#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartQueen : public ChessPart
{
    public:

    ChessPartQueen(ChessMesh meshList, int color){

            m_model = &meshList.m_Reine;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible() override {
            
            return std::vector<int>();
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 5;
};