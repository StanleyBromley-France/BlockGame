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

#include "CubeInstance.h"

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

    const int gridSize = 100;
    const float spacing = 1.0f;
    const float noiseScale = 1.0f;

    // Define the 1D array size based on gridSize and maxHeight (5)
    const int maxHeight = 5;
    const int totalCubes = gridSize * gridSize * maxHeight;
    CubeInstance* cubes = new CubeInstance[totalCubes];


    // create and configure the noise generator
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);  // chooses the noise type
    noise.SetFrequency(0.1f);  // adjusts the frequency for the smoothness of the noise
    noise.SetSeed(12345);  // sets a seed for reproducibility

    // initialises the cubes with positions and random heights
    // Precompute cubes in the 1D array
    for (int x = 0; x < gridSize; ++x) {
        for (int z = 0; z < gridSize; ++z) {
            // Generate noise value for this (x, z) coordinate
            float noiseValue = noise.GetNoise(x * noiseScale, z * noiseScale);

            // Map noise value from [-1, 1] to [0, 5] for height
            int height = static_cast<int>((noiseValue + 1.0f) * 2.5f);
            height = std::clamp(height, 0, maxHeight);

            // Populate the cubes array using the computed index
            for (int y = 0; y < height; ++y) {
                glm::vec3 position(x * spacing, y * spacing, z * spacing);
                int index = (z * gridSize * maxHeight) + (x * maxHeight) + y;
                cubes[index] = CubeInstance(position);
            }
        }
    }
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        GLFWHelper::UpdateTime();

        // input
        GLFWHelper::processInput(window);

        GladHelper::ClearScreen();

        // activates shader
        CubeMesh::GetInstance().GetShader().use();

        // pass projection matrix to shader
        CubeMesh::GetInstance().GetShader().SetMat4("projection", GLFWHelper::Projection());

        // camera/view transformation
        glm::mat4 view = glm::mat4(1.0f);
        view = GLFWHelper::LookAt();
        CubeMesh::GetInstance().GetShader().SetMat4("view", view);

        glBindVertexArray(CubeMesh::GetInstance().GetMeshBuffers().getVAO());
        for (int x = 0; x < gridSize; ++x) {
            for (int z = 0; z < gridSize; ++z) {
                for (int y = 0; y < maxHeight; ++y) {
                    int index = (z * gridSize * maxHeight) + (x * maxHeight) + y;
                    CubeInstance& cube = cubes[index];
                    cube.Render();
                }
            }
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

        calculateFPS(window);
    }

    for (int x = 0; x < gridSize; ++x) {
        for (int z = 0; z < gridSize; ++z) {
            for (int y = 0; y < maxHeight; ++y) {
                int index = (z * gridSize * maxHeight) + (x * maxHeight) + y;
                CubeInstance& cube = cubes[index];
                cube.DeAllocate();
            }
        }
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}