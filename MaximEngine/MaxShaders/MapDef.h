///////////////////
//
// Map of MapUnits (1/100th of sqm (10cm X 10cm)) containing height, objects: one per square meter maximum "An object == a 3d bitmap of maximum 25m X 25m X 25m"
// Memory of today allows that system to be implemented easily, the shader-robot will be 2 meters tall to enter the buildings and other objects
//
////////////////////


#include "MapUnit.h"
#include <Tools.h>
#include <Picking.h>

class MapDef 
{

    public:

        MapDef(int width, int length) 
        {
            mapWidth = width;
            mapLength = length;

            mapUnits = new MapUnit*[mapLength * mapWidth];

            for (int i = 0; i < mapLength * mapWidth; i++) 
            {
                mapUnits[i] = new MapUnit();
            }
        }

        ~MapDef() 
        {
            for (int i = 0; i < mapLength * mapWidth; i++) 
            {
                delete mapUnits[i];
            }
        }

        MapUnit& getMapUnit(int x, int y) 
        {
            return *mapUnits[y * mapWidth + x];
        }

        float getDistanceRayCast(VulkanCookbook::Vector3 ray_origin, VulkanCookbook::Vector3 ray_vector)
        {

            //for(int i = 0; i < mapUnits)
            ray_intersects_triangle( ray_origin, ray_vector, nullptr, 0, glm::mat4(1.0f));

            return -1.0f;
        }   

    private:

        MapUnit** mapUnits;

        int mapWidth;
        int mapLength;
};