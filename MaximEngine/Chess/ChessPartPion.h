#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartPion : public ChessPart
{
    public:

        ChessPartPion(ChessMesh meshList){

            m_model = &meshList.m_Pion;
        }

        std::vector<int> deplacementPossible() override {
            
            return std::vector<int>();
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 0;
};