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

private:
    Shader Shader;
    GladHelper::MeshBuffers MeshBuffers;
};
#endif