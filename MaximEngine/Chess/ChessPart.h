#include<vector>

#include "CHessCase.h"

#include "CookbookSampleFramework.h"

class ChessPart : ChessCase
{
    public:

        virtual std::vector<int> deplacementPossible() = 0;

    private:

        virtual void loadModel() = 0;

    private:
    
        VulkanCookbook::Mesh m_model;
};