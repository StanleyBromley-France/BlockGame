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

    const int gridSize = 10;
    const float spacing = 1.0f;
    const float noiseScale = 1.0f;

    // creates a 3D array of Cube objects
    CubeInstance cubes[gridSize][gridSize][5]; // fixed maximum height of 5

    // create and configure the noise generator
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);  // chooses the noise type
    noise.SetFrequency(0.1f);  // adjusts the frequency for the smoothness of the noise
    noise.SetSeed(12345);  // sets a seed for reproducibility

    // initialises the cubes with positions and random heights
    for (int x = 0; x < gridSize; ++x) {
        for (int z = 0; z < gridSize; ++z) {
            // generates a noise value for this (x, z) coordinate
            float noiseValue = noise.GetNoise(x * noiseScale, z * noiseScale);

            // maps noise value from [-1, 1] to [0, 5] for height
            int height = static_cast<int>((noiseValue + 1.0f) * 2.5f);

            // clamps the height to the range [0, 5]
            //height = std::clamp(height, 0, 5);

            // populates the cubes up to the random height
            for (int y = 0; y < height; ++y) {
                glm::vec3 position(x * spacing, y * spacing, z * spacing);
                cubes[x][z][y] = CubeInstance(position);
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

        for (auto& plane : cubes) {
            for (auto& row : plane) {
                for (auto& cube : row) {
                    cube.Render();
                }
            }
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto& plane : cubes) {
        for (auto& row : plane) {
            for (auto& cube : row) {
                cube.DeAllocate();
            }
        }
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}