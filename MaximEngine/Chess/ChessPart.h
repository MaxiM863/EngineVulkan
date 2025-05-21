#ifndef CHESS_PART
#define CHESS_PART

#include<vector>

#include "CookbookSampleFramework.h"

class ChessPart
{
    public:

        ChessPart(){};

        virtual std::vector<int> deplacementPossible(int position, std::vector<int> occupe, std::vector<ChessPart*> parts, int color, bool isPion, int& mange) = 0;
        virtual int getBufferDraw() = 0;

        bool isOpponant(int position, int color, std::vector<ChessPart*> parts)
        {
            if(parts.at(position) != nullptr && parts.at(position)->colorPart != color) return true;
            
            return false;
        }

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
        
        int colorPart;
};

#endif