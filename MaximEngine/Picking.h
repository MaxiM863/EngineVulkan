#include <optional>
#include <limits>
#include <Tools.h>

struct Triangle {

    VulkanCookbook::Vector3 a;
    VulkanCookbook::Vector3 b;
    VulkanCookbook::Vector3 c;


};

using namespace VulkanCookbook;

std::optional<VulkanCookbook::Vector3> ray_intersects_triangle( const VulkanCookbook::Vector3 &ray_origin,
    const VulkanCookbook::Vector3 &ray_vector,
    const float* mesh, int nbrVertices)
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    
    for(int i = 0; i < nbrVertices/9; i++)
    {
        Triangle triangle;

        triangle.a[0] = mesh[9*i+0];
        triangle.a[1] = mesh[9*i+1];
        triangle.a[2] = mesh[9*i+2];
        
        triangle.b[0] = mesh[9*i+3];
        triangle.b[1] = mesh[9*i+4];
        triangle.b[2] = mesh[9*i+5];

        triangle.c[0] = mesh[9*i+6];
        triangle.c[1] = mesh[9*i+7];
        triangle.c[2] = mesh[9*i+8];
        
        VulkanCookbook::Vector3 edge1 = triangle.b - triangle.a;
        VulkanCookbook::Vector3 edge2 = triangle.c - triangle.a;
        VulkanCookbook::Vector3 ray_cross_e2 = VulkanCookbook::Cross(ray_vector, edge2);
        float det = VulkanCookbook::Dot(edge1, ray_cross_e2);

        if (det > -epsilon && det < epsilon)
            return {};    // This ray is parallel to this triangle.

        float inv_det = 1.0 / det;
        VulkanCookbook::Vector3 s = ray_origin - triangle.a;
        float u = inv_det * VulkanCookbook::Dot(s, ray_cross_e2);

        if ((u < 0 && abs(u) > epsilon) || (u > 1 && abs(u-1) > epsilon))
            return {};

            VulkanCookbook::Vector3 s_cross_e1 = VulkanCookbook::Cross(s, edge1);
        float v = inv_det * VulkanCookbook::Dot(ray_vector, s_cross_e1);

        if ((v < 0 && abs(v) > epsilon) || (u + v > 1 && abs(u + v - 1) > epsilon))
            return {};

        // At this stage we can compute t to find out where the intersection point is on the line.
        float t = inv_det * VulkanCookbook::Dot(edge2, s_cross_e1);

        if (t > epsilon) // ray intersection
        {
            return  VulkanCookbook::Vector3(ray_origin + ray_vector * t);
        }
        else // This means that there is a line intersection but not a ray intersection.
            return {};
    }
}