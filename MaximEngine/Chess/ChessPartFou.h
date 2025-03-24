#include "ChessPart.h"
#include "ChessMesh.h"


class ChessPartFou : public ChessPart
{
    public:

        ChessPartFou(ChessMesh meshList, int color){

            m_model = &meshList.m_Fou;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, int color, bool isPion) override {
            
            std::vector<int> rep;

            for(int i = 0; i < 8; i++)
            {

                if(position + (i+1)*(8+1) < 64)
                {
                    
                    if(isOccupied(position+(i+1)*(8+1), occupe))
                    {
                    
                        break;
                    }
                    else
                    {
                        
                        rep.push_back(position+(i+1)*(8+1));
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position + (i+1)*(8-1) < 64)
                {
                    
                    if(isOccupied(position+(i+1)*(8-1), occupe))
                    {
                    
                        break;
                    }
                    else
                    {
                        
                        rep.push_back(position+(i+1)*(8-1));
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8+1) < 64)
                {
                    
                    if(isOccupied(position - (i+1)*(8 + 1), occupe))
                    {
                    
                        break;
                    }
                    else
                    {
                        
                        rep.push_back(position - (i+1)*(8 + 1));
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                if(position - (i+1)*(8-1) < 64)
                {
                    
                    if(isOccupied(position - (i+1)*(8-1), occupe))
                    {
                    
                        break;
                    }
                    else
                    {
                        
                        rep.push_back(position - (i+1)*(8-1));
                    }
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

        int bufferDraw = 4;
};