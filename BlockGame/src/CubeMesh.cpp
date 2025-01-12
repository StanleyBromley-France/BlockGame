#include "CubeMesh.h"

// sets up cube model class, called first time getInstance is run
CubeMesh::CubeMesh() : Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl")
{
    float vertices[] = {
        // Positions          // Texture Coords

        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // Bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-left

        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // Top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // Top-left

        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // Bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // Top-left

        // Right face
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // Bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // Top-left

         // Bottom face
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-right
          0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
         -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // Top-left

         // Top face
         -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
          0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-right
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f   // Top-left
    };

    unsigned int indices[] = {
        // Front face
        0, 1, 2,  2, 3, 0,
        // Back face
        4, 7, 6, 6, 5, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 15, 14, 14, 13, 12,
        // Bottom face
        16, 17, 18, 18, 19, 16,
        // Top face
        20, 23, 22, 22, 21, 20
    };

    MeshBuffers = GladHelper::MeshBuffers();

    MeshBuffers.SetupMeshBuffers(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));
    unsigned int texture1 = GladHelper::loadTexture("container.jpg");
    unsigned int texture2 = GladHelper::loadTexture("awesomeface.png", false);

    Shader.use();
    Shader.SetInt("texture1", 0); // assigns texture1 to texture unit 0
    Shader.SetInt("texture2", 1); // assigns texture2 to texture unit 1

    // binds textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
}

Shader& CubeMesh::GetShader() 
{
    return Shader;
}

GladHelper::MeshBuffers& CubeMesh::GetMeshBuffers()
{
    return MeshBuffers;
}