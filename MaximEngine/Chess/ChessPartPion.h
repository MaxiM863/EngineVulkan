#include "ChessPart.h"
#include "ChessMesh.h"

class ChessPartPion : public ChessPart
{
    public:

        ChessPartPion(ChessMesh meshList, int color){

            m_model = &meshList.m_Pion;
            this->colorPart = color;
        }

        std::vector<int> deplacementPossible(int position, std::vector<int> occupe, int color, bool isPion) override {
            
            std::vector<int> rep;

            int switchColor = 1;

            if(color == 1) switchColor = -1;
            
            if(position + switchColor * 8 < 64 && position + switchColor * 8 >= 0 && !isOccupied(position + switchColor * 8, occupe))
            {
                rep.push_back(position + switchColor * 8);
            }

            if(position/8 == 6 || position/8 == 1)
            {
                if(position + switchColor * 16 < 64 && position + switchColor * 16 >= 0 && !isOccupied(position + switchColor * 16, occupe))
                {
                    rep.push_back(position + switchColor * 16);
                }
            }

            if(position%8 == 7)
            {
                if(isOccupied(position - 1, occupe))
                {
                    rep.push_back(position - switchColor * (1));
                }
            }
            else if(position%8 == 0)
            {
                if(isOccupied(position + 1, occupe))
                {
                    rep.push_back(position + switchColor * (1));
                }
            }
            else
            {
                if(isOccupied(position + 1, occupe))
                {
                    rep.push_back(position + switchColor * (1));
                }
                if(isOccupied(position - 1, occupe))
                {
                    rep.push_back(position - switchColor * (1));
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

        int bufferDraw = 0;
};