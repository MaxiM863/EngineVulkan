#ifndef CHESS_CASE
#define CHESS_CASE

#include "ChessPart.h"

class ChessCase
{
    public:

        ChessCase(){};
        ChessCase(ChessPart* part){ this->part = part; };

        bool isEmpty() { return part == nullptr; }
        ChessPart* getPart() { return part; }

    private:

        ChessPart* part = nullptr;

};

#endif