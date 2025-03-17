#ifndef CHESS_PART
#define CHESS_PART

#include<vector>

#include "ChessCase.h"

#include "CookbookSampleFramework.h"

class ChessPart : ChessCase
{
    public:

        ChessPart(){};
        ChessPart(ChessPart* part){ m_part = part;}

        virtual std::vector<int> deplacementPossible() = 0;

    private:

        virtual void loadModel() = 0;

    public:
    
        VulkanCookbook::Mesh m_model;

    private:

        ChessPart* m_part;
    
        
};

#endif