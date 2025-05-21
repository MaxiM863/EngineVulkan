#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartTour : public ChessPart
{
    public:

        ChessPartTour(ChessMesh meshList, int color){

            m_model = &meshList.m_Tour;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, std::vector<ChessPart*> parts, int color, bool isPion, int& mange) override {
            
            std::vector<int> rep;

            for(int i = 0; i < 8; i++)
            {

                if(position + (i+1)*(8) < 64)
                {
                    if(isOpponant(position + (i+1)*(8), color, parts)) rep.push_back(position+(i+1)*(8));
                    if(isOccupied(position+(i+1)*(8), occupe)) break;
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(1) < 64)
                {
                    if(isOpponant(position + (i+1)*(1), color, parts)) rep.push_back(position+(i+1)*(1));
                    if(isOccupied(position+(i+1)*(1), occupe)) break;
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(1) < 64)
                {
                    if(isOpponant(position - (i+1)*(1), color, parts)) rep.push_back(position - (i+1)*(1));
                    if(isOccupied(position - (i+1)*(1), occupe)) break;
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8) < 64)
                {
                    if(isOpponant(position - (i+1)*(8), color, parts)) rep.push_back(position - (i+1)*(8));
                    if(isOccupied(position - (i+1)*(8), occupe)) break;
                }
            }

            return rep;
        }

        int getBufferDraw() override { return bufferDraw; }
             
        VulkanCookbook::Mesh* m_model;

        

    private:

        bool isOccupied(int position, std::vector<int> present)
        {
            bool rep = false;

            for(int i = 0; i < present.size(); i++)
            {
                if(present.at(i) == position)
                {
                    rep = true;
                    break;
                }
            }

            return rep;
        }

        int bufferDraw = 1;
};