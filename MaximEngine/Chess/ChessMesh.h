#ifndef CHESS_MESH
#define CHESS_MESH

#include "CookbookSampleFramework.h"

class ChessMesh{

    public:

        ChessMesh(){

            Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, false, false, true, m_Tour );
            /*Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, false, false, false, m_Cavalier );
            Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, false, false, false, m_Fou );
            Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, false, false, false, m_Roi );
            Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, false, false, false, m_Reine );*/
            Load3DModelFromObjFile( "Data/Models/chess_pion.obj", true, false, false, true, m_Pion );
        }

        VulkanCookbook::Mesh m_Tour;
        VulkanCookbook::Mesh m_Cavalier;
        VulkanCookbook::Mesh m_Fou;
        VulkanCookbook::Mesh m_Roi;
        VulkanCookbook::Mesh m_Reine;
        VulkanCookbook::Mesh m_Pion;
};

#endif