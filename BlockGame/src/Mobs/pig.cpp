#include "pig.h"

#include "../GLFWHelper.h"

ImportedModel* Pig::importedModel = nullptr;
Shader* Pig::shader = nullptr;

// Constructor
Pig::Pig(const glm::vec3& position) : position(position) {
    if (!importedModel || !shader) {
        LoadResources(); // loads the model and shader if not already loaded
    }
}

// Render the zombie
void Pig::Render() {
    shader->use();

    // pass projection matrix to shader
    shader->SetMat4("projection", GLFWHelper::Projection());

    // camera/view transformation
    glm::mat4 view = glm::mat4(1.0f);
    view = GLFWHelper::LookAt();
    shader->SetMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position); // translates model to given position
    model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// resizes model
    shader->SetMat4("model", model);

    importedModel->Draw(*shader);
}

// getter for position
glm::vec3 Pig::GetPosition() {
    return position;
}

// loads the static model and shader resources
void Pig::LoadResources() {
    if (!importedModel) {
        importedModel = new ImportedModel("objects/pig/pig.glb");
    }
    if (!shader) {
        shader = new Shader("shaders/model_import_vertex.glsl", "shaders/model_import_frag.glsl");
    }
}