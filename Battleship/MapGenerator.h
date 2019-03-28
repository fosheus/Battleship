#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "PerlinNoise.h"
#include "DEFINITIONS.h"


class MapGenerator
{
public :
	enum CellType {
		WATER,
		BEACH,
		ISLAND
	};

private:
	float *fNoiseSeed2D = nullptr;
	float *fPerlinNoise2D = nullptr;
	int nOctaveCount = 5;
	float fScalingBias = 0.4f;
	std::vector<sf::Vector2i> walls;
	std::vector<std::vector<CellType>> matrix;
public:
	MapGenerator();
	std::vector<std::vector<CellType>>& generate();
	std::vector<sf::Vector2i>& getWalls();
	/**
	* Returns 1 if position is of type, 0 otherwise
	* if position not in range, returns -1
	*/	
	~MapGenerator();
};

