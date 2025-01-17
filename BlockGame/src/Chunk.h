#ifndef CHUNK_H
#define CHUNK_H

#include <map>
#include <vector>
#include <FastNoiseLite.h>

#include "CubeInstance.h"
#include "Biomes.h"
#include "GladHelper.h"

class Chunk {
public:
	Chunk(glm::vec3 position, Biomes::Biome currentBiome, FastNoiseLite noise);
	void RenderChunk();
	void Deallocate();
private:
	CubeMesh Mesh;
	Biomes::Biome currentBiome;
	std::vector<glm::mat4> modelMatrices;
	glm::vec3 chunkPos;
	unsigned int chunkBuffer;
	static const int chunkSize = 16;
	static const int chunkHeight = 32;
	CubeInstance*** cubes;
};
#endif