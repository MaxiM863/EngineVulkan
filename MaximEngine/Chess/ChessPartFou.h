#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartFou : public ChessPart
{
    public:

        ChessPartFou(ChessMesh meshList, int color){

            m_model = &meshList.m_Fou;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, std::vector<ChessPart*> parts, int color, bool isPion, int& mange) override {
            
            std::vector<int> rep;

            for(int i = 0; i < 8; i++)
            {

                if(position + (i+1)*(8+1) < 64)
                {
                
                    if(isOpponant(position + (i+1)*(8+1), color, parts)) rep.push_back(position+(i+1)*(8+1));
                    if(isOccupied(position+(i+1)*(8+1), occupe) || (position + (i+1)*(8+1)) % 8 == 7) break;                    
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(8-1) < 64)
                {
                    if(isOpponant(position + (i+1)*(8-1), color, parts)) rep.push_back(position+(i+1)*(8-1));
                    if(isOccupied(position+(i+1)*(8-1), occupe) || (position + (i+1)*(8-1)) % 8 == 0) break;
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8+1) >= 0)
                {
                    if(isOpponant(position - (i+1)*(8+1), color, parts)) rep.push_back(position - (i+1)*(8 + 1));
                    if(isOccupied(position - (i+1)*(8 + 1), occupe) || (position - (i+1)*(8+1)) % 8 == 7) break;
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8-1) >= 0)
                {
                    if(isOpponant(position - (i+1)*(8-1), color, parts)) rep.push_back(position - (i+1)*(8-1));
                    if(isOccupied(position - (i+1)*(8-1), occupe) || (position + (i+1)*(8+1)) % 8 == 0) break;
                }
            }

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        



        int bufferDraw = 4;
};