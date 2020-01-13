#pragma once
#ifndef __CUBE_WRAPPED_H__
#define __CUBE_WRAPPED_H__ 1

#include "geometry.hpp"

class Cube_wrapped final : public Geometry {
public:
    Cube_wrapped() = delete;
    explicit Cube_wrapped(float size);

private:
    float _size;
};
#endif