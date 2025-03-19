#include "ChessPart.h"

class ChessPartPion : public ChessPart
{
    public:

        ChessPartPion(){}

        std::vector<int> deplacementPossible() override {
            
            return std::vector<int>();
        }

        void loadModel() override {

            Load3DModelFromObjFile( "Data/Models/chess_pion.obj", true, false, false, true, m_model );
        }
    private:

};