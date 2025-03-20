#ifndef CHESS_PART
#define CHESS_PART

#include<vector>

#include "CookbookSampleFramework.h"

class ChessPart
{
    public:

        ChessPart(){};

        virtual std::vector<int> deplacementPossible() = 0;
        virtual int getBufferDraw() = 0;
        
        int colorPart;
};

#endif