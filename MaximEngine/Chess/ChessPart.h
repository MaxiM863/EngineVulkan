#ifndef CHESS_PART
#define CHESS_PART

#include<vector>

#include "CookbookSampleFramework.h"

#include "ChessBoard.h"

class ChessPart
{
    public:

        ChessPart(){};

        virtual std::vector<int> deplacementPossible(int position, ChessBoard board) = 0;
        virtual int getBufferDraw() = 0;
        
        int colorPart;
};

#endif