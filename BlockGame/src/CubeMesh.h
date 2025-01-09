#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "Shader.h"
#include "GladHelper.h"

class CubeMesh
{
public:
    static CubeMesh& GetInstance();

    Shader& GetShader();
    GladHelper::MeshBuffers& GetMeshBuffers();

private:
    CubeMesh();
    // prevents creating another instance of this class in code
    CubeMesh(const CubeMesh&) = delete;
    CubeMesh& operator=(const CubeMesh&) = delete;

    Shader Shader;
    GladHelper::MeshBuffers MeshBuffers;
};
#endif