#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__ 1
#include <cstdint>
#include <glad/glad.h>

//0 posiciones
//1 uvs
//2 normales

class Geometry {
    public:
        Geometry() = default;

        virtual void render() const = 0;

        virtual ~Geometry() {
            glDeleteVertexArrays(1, &_VAO);
            glDeleteBuffers(4, _VBO);
        }
    protected:
        uint32_t _VAO = 0;
        uint32_t _VBO[4]{ 0,0,0,0 };
        uint32_t _nVerts = 0;

};
#endif