
#include "ChessPart.h"

class ChessCase
{
    public:

        bool isEmpty() { return part == nullptr; }
        ChessPart* getPart() { return part; }

    private:

        ChessPart* part = nullptr;

};