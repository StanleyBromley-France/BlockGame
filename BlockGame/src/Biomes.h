#ifndef BIOMES_H
#define BIOMES_H

#include "CubeMesh.h"
namespace Biomes {
    struct Biome {
        float noiseScale;
        int heightScale;
        CubeMesh::Texture texture;
    };

    inline const Biome mountainousBiome = {
        0.7f,
        20,
        CubeMesh::Texture::STONE
    };

    inline const Biome hillyBiome = {
        0.3f,
        10,  
        CubeMesh::Texture::DIRT
    };

    inline const Biome desertBiome = {
        0.1f,
        5,
        CubeMesh::Texture::SAND
    };
}

#endif