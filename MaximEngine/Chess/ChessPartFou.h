#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartFou : public ChessPart
{
    public:

        ChessPartFou(ChessMesh meshList, int color){

            m_model = &meshList.m_Fou;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible() override {
            
            return std::vector<int>();
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 4;
};