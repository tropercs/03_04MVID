#ifndef __CUBE_POSITIONED_H__
#define __CUBE_POSITIONED_H__ 1

#include "geometry.hpp"
#include <glm\ext\vector_float3.hpp>

class Cube_positioned final : public Geometry {
    public:
        Cube_positioned() = delete;
        explicit Cube_positioned(float radius, glm::vec3 center);

    private:
        float _radius;
        glm::vec3 _center;
};
#endif