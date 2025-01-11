#include "Chunk.h"

#include <FastNoiseLite.h>
#include <algorithm>
#include <cstdlib>

Chunk::Chunk(glm::vec3 position, Biomes::Biome currentBiome) : chunkPos(position) {
    const float spacing = 1.0f;

    // Create and configure the noise generator
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);  // Choose the noise type
    noise.SetFrequency(0.1f);  // Adjusts the frequency for the smoothness of the noise
    noise.SetSeed((rand() % 1000 + 1));  // Sets a seed for reproducibility

    // Dynamically allocate the cubes array on the heap
    cubes = new CubeInstance * *[chunkSize];
    for (int x = 0; x < chunkSize; ++x) {
        cubes[x] = new CubeInstance * [chunkSize];
        for (int z = 0; z < chunkSize; ++z) {
            cubes[x][z] = new CubeInstance[chunkHeight];
        }
    }

    // Initialises the cubes with positions and random heights
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            // Generates a noise value for this (x, z) coordinate
            float noiseValue = noise.GetNoise(x * currentBiome.noiseScale, z * currentBiome.noiseScale);

            // Maps noise value from [-1, 1] to [0, 5] for height
            int height = static_cast<int>((noiseValue + 1.0f) * currentBiome.heightScale);
            // Clamps the height to the range [0, 5]
            height = std::clamp(height, 1, chunkHeight);

            // Populates the cubes up to the random height
            for (int y = 0; y < height; ++y) {
                glm::vec3 position(x * spacing, y * spacing, z * spacing);
                cubes[x][z][y] = CubeInstance(position + chunkPos);
            }
        }
    }
}

void Chunk::RenderChunk()
{
    Shader& shader = CubeMesh::GetInstance().GetShader();
    // activates shader
    shader.use();

    // pass projection matrix to shader
    shader.SetMat4("projection", GLFWHelper::Projection());

    // camera/view transformation
    glm::mat4 view = glm::mat4(1.0f);
    view = GLFWHelper::LookAt();
    shader.SetMat4("view", view);

    // render cube
    glBindVertexArray(CubeMesh::GetInstance().GetMeshBuffers().getVAO());

    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            for (int y = 0; y < chunkHeight; ++y) {
                cubes[x][z][y].Render();  // Render each cube
            }
        }
    }
}
