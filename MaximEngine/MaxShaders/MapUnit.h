#include <vector>

struct MapUnit 
{

    public:

        unsigned char translationObject_X_Y = 0; //two 4-bits for X and Y translation of the object in the map unit

        unsigned short height = 0;

        std::vector<unsigned short> positionOfObject; // position of the object in the chain list ==> 0 = no object
};