#include "CubeInstance.h"

// constructor to initialise cube with textures
CubeInstance::CubeInstance(const glm::vec3& position) : position(position), Mesh(&CubeMesh::GetInstance()) {}

// renders the cube
void CubeInstance::Render()
{
    Shader& shader = Mesh->GetShader();

    // activates shader
    shader.use();

    // pass projection matrix to shader
    shader.SetMat4("projection", GLFWHelper::Projection());

    // camera/view transformation
    glm::mat4 view = glm::mat4(1.0f);
    view = GLFWHelper::LookAt();
    shader.SetMat4("view", view);

    // render cube
    glBindVertexArray(Mesh->GetMeshBuffers().getVAO());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position); // Modify model matrix
    shader.SetMat4("model", model);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void CubeInstance::DeAllocate() 
{
    Mesh->GetMeshBuffers().DeAllocate();
}