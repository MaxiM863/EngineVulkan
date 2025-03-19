class ChessPartTour
{
    public:

        ChessPartTour(){
        }

        std::vector<int> deplacementPossible() {

            return std::vector<int>();
        }

        void loadModel() {

            Load3DModelFromObjFile( "Data/Models/chess_tour.obj", true, false, false, false, m_model );
        }
        
        VulkanCookbook::Mesh m_model;

    private:

};