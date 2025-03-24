#ifndef CHESS_PART
#define CHESS_PART

#include<vector>

#include "CookbookSampleFramework.h"

class ChessPart
{
    public:

        ChessPart(){};

        virtual std::vector<int> deplacementPossible(int position, std::vector<int> occupe, int color, bool isPion) = 0;
        virtual int getBufferDraw() = 0;
        
        int colorPart;
};

#endif