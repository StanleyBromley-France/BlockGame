#ifndef CHUNK_H
#define CHUNK_H

#include <map>

#include "CubeInstance.h"
#include "Biomes.h"



class Chunk {
public:
	Chunk(glm::vec3 position, Biomes::Biome currentBiome);
	void RenderChunk();
private:
	glm::vec3 chunkPos;
	static const int chunkSize = 16;
	static const int chunkHeight = 32;
	CubeInstance*** cubes;
};
#endif