#ifndef BIOMES_H
#define BIOMES_H

namespace Biomes {
    struct Biome {
        float noiseScale;
        int heightScale;
    };

    inline const Biome mountainousBiome = {
        0.7f,
        20 
    };

    inline const Biome hillyBiome = {
        0.3f,
        10  
    };

    inline const Biome desertBiome = {
        0.1f,
        5
    };
}

#endif