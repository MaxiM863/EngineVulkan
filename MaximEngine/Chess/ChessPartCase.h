#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartCase : public ChessPart
{
    public:

        ChessPartCase(ChessMesh meshList, int color){

            m_model = &meshList.m_Case;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, std::vector<ChessPart*>, int color, bool isPion, int& mange) override {
            
            return std::vector<int>();
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        int bufferDraw = 6;
};