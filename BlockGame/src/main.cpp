#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <FastNoiseLite.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "GLFWHelper.h"
#include "GladHelper.h"

#include <algorithm>
#include <iostream>

#include "Biomes.h"
#include "Chunk.h"

double lastTime = 0.0;
int frameCount = 0;
double frameTime = 0.0;

void calculateFPS(GLFWwindow* window) {
    double currentTime = glfwGetTime();
    frameTime = currentTime - lastTime;
    frameCount++;
    // Update FPS every second
    if (frameTime >= 1.0) {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        lastTime = currentTime;
    }
}



int main()
{
    // window creation
    GLFWwindow* window = GLFWHelper::initialiseAndConfigure();

    if (window == NULL) // makes sure window exists
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glad creation
    if (!GladHelper::initialiseAndConfigure())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Define the chunks in a 5x5 grid with diverse biomes
    // Row 1 (top row) - mixed biomes
    Chunk desertChunk1 = Chunk::Chunk(glm::vec3(0.0f, 0.0f, 0.0f), Biomes::desertBiome);
    Chunk hillyChunk1 = Chunk::Chunk(glm::vec3(16.0f, 0.0f, 0.0f), Biomes::hillyBiome);
    Chunk mountainousChunk1 = Chunk::Chunk(glm::vec3(32.0f, 0.0f, 0.0f), Biomes::mountainousBiome);
    Chunk desertChunk2 = Chunk::Chunk(glm::vec3(48.0f, 0.0f, 0.0f), Biomes::desertBiome);
    Chunk hillyChunk2 = Chunk::Chunk(glm::vec3(64.0f, 0.0f, 0.0f), Biomes::hillyBiome);

    // Row 2 - mixed biomes
    Chunk hillyChunk3 = Chunk::Chunk(glm::vec3(0.0f, 0.0f, 16.0f), Biomes::hillyBiome);
    Chunk mountainousChunk2 = Chunk::Chunk(glm::vec3(16.0f, 0.0f, 16.0f), Biomes::mountainousBiome);
    Chunk desertChunk3 = Chunk::Chunk(glm::vec3(32.0f, 0.0f, 16.0f), Biomes::desertBiome);
    Chunk hillyChunk4 = Chunk::Chunk(glm::vec3(48.0f, 0.0f, 16.0f), Biomes::hillyBiome);
    Chunk mountainousChunk3 = Chunk::Chunk(glm::vec3(64.0f, 0.0f, 16.0f), Biomes::mountainousBiome);

    // Row 3 - mixed biomes
    Chunk mountainousChunk4 = Chunk::Chunk(glm::vec3(0.0f, 0.0f, 32.0f), Biomes::mountainousBiome);
    Chunk desertChunk4 = Chunk::Chunk(glm::vec3(16.0f, 0.0f, 32.0f), Biomes::desertBiome);
    Chunk hillyChunk5 = Chunk::Chunk(glm::vec3(32.0f, 0.0f, 32.0f), Biomes::hillyBiome);
    Chunk mountainousChunk5 = Chunk::Chunk(glm::vec3(48.0f, 0.0f, 32.0f), Biomes::mountainousBiome);
    Chunk desertChunk5 = Chunk::Chunk(glm::vec3(64.0f, 0.0f, 32.0f), Biomes::desertBiome);

    // Row 4 - mixed biomes
    Chunk desertChunk6 = Chunk::Chunk(glm::vec3(0.0f, 0.0f, 48.0f), Biomes::desertBiome);
    Chunk hillyChunk6 = Chunk::Chunk(glm::vec3(16.0f, 0.0f, 48.0f), Biomes::hillyBiome);
    Chunk mountainousChunk6 = Chunk::Chunk(glm::vec3(32.0f, 0.0f, 48.0f), Biomes::mountainousBiome);
    Chunk desertChunk7 = Chunk::Chunk(glm::vec3(48.0f, 0.0f, 48.0f), Biomes::desertBiome);
    Chunk hillyChunk7 = Chunk::Chunk(glm::vec3(64.0f, 0.0f, 48.0f), Biomes::hillyBiome);

    // Row 5 (bottom row) - mixed biomes
    Chunk hillyChunk8 = Chunk::Chunk(glm::vec3(0.0f, 0.0f, 64.0f), Biomes::hillyBiome);
    Chunk mountainousChunk7 = Chunk::Chunk(glm::vec3(16.0f, 0.0f, 64.0f), Biomes::mountainousBiome);
    Chunk desertChunk8 = Chunk::Chunk(glm::vec3(32.0f, 0.0f, 64.0f), Biomes::desertBiome);
    Chunk hillyChunk9 = Chunk::Chunk(glm::vec3(48.0f, 0.0f, 64.0f), Biomes::hillyBiome);
    Chunk mountainousChunk8 = Chunk::Chunk(glm::vec3(64.0f, 0.0f, 64.0f), Biomes::mountainousBiome);



    // render loop
    while (!glfwWindowShouldClose(window))
    {
        GLFWHelper::UpdateTime();

        // input
        GLFWHelper::processInput(window);

        GladHelper::ClearScreen();

        // Render all chunks in the 5x5 grid
        desertChunk1.RenderChunk();
        hillyChunk1.RenderChunk();
        mountainousChunk1.RenderChunk();
        desertChunk2.RenderChunk();
        hillyChunk2.RenderChunk();

        hillyChunk3.RenderChunk();
        mountainousChunk2.RenderChunk();
        desertChunk3.RenderChunk();
        hillyChunk4.RenderChunk();
        mountainousChunk3.RenderChunk();

        mountainousChunk4.RenderChunk();
        desertChunk4.RenderChunk();
        hillyChunk5.RenderChunk();
        mountainousChunk5.RenderChunk();
        desertChunk5.RenderChunk();

        desertChunk6.RenderChunk();
        hillyChunk6.RenderChunk();
        mountainousChunk6.RenderChunk();
        desertChunk7.RenderChunk();
        hillyChunk7.RenderChunk();

        hillyChunk8.RenderChunk();
        mountainousChunk7.RenderChunk();
        desertChunk8.RenderChunk();
        hillyChunk9.RenderChunk();
        mountainousChunk8.RenderChunk();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

        calculateFPS(window);
    }

    CubeMesh::GetInstance().GetMeshBuffers().DeAllocate();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}