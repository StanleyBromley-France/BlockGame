#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "Shader.h"
#include "GladHelper.h"

class CubeMesh
{
public:
    CubeMesh();

    Shader& GetShader();
    GladHelper::MeshBuffers& GetMeshBuffers();

    enum class Texture
    {
        SAND,
        DIRT,
        STONE
    };

    void SwitchTexture(Texture texture);

private:
    Shader Shader;
    GladHelper::MeshBuffers MeshBuffers;

    unsigned int sandTexture;
    unsigned int dirtTexture;
    unsigned int stoneTexture;

};
#endif