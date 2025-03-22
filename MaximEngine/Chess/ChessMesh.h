#ifndef CHESS_MESH
#define CHESS_MESH

#include "CookbookSampleFramework.h"

class ChessMesh{

    public:

        ChessMesh(){           

            Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, true, true, true, m_Tour, &stride );
            Load3DModelFromObjFile( "Data/Models/chess_cavalier.obj", true, true, true, true, m_Cavalier );
            Load3DModelFromObjFile( "Data/Models/chess_fou.obj", true, true, true, true, m_Fou );
            Load3DModelFromObjFile( "Data/Models/chess_king.obj", true, true, true, true, m_Roi );
            Load3DModelFromObjFile( "Data/Models/chess_queen.obj", true, true, true, true, m_Reine );
            Load3DModelFromObjFile( "Data/Models/chess_Pion.obj", true, true, true, true, m_Pion );
            Load3DModelFromObjFile( "Data/Models/case.obj", true, true, true, true, m_Case );
        }

        VulkanCookbook::Mesh m_Tour;
        VulkanCookbook::Mesh m_Cavalier;
        VulkanCookbook::Mesh m_Fou;
        VulkanCookbook::Mesh m_Roi;
        VulkanCookbook::Mesh m_Reine;
        VulkanCookbook::Mesh m_Pion;
        VulkanCookbook::Mesh m_Case;

        uint32_t stride;
};

#endif