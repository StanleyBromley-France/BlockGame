#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "Shader.h"
#include "GladHelper.h"

class CubeMesh
{
public:
    CubeMesh();

    enum class Texture
    {
        SAND,
        DIRT,
        STONE
    };

    Shader& GetShader(Texture texture);
    GladHelper::MeshBuffers& GetMeshBuffers();


    void SwitchTexture(Texture texture);

private:
    Shader ShaderSingle;
    Shader ShaderMixed;
    GladHelper::MeshBuffers MeshBuffers;

    unsigned int sandTexture;
    unsigned int dirtTexture;
    unsigned int stoneTexture;

};
#endif