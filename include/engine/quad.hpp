#ifndef __QUAD_H__
#define __QUAD_H__ 1

#include "engine/geometry.hpp"

//0 posiciones
//1 uvs
//2 normales

class Quad: public Geometry {
public:
    Quad() = delete;
    explicit Quad(float size);

    void render() const override;
protected:
    float _size;

};
#endif