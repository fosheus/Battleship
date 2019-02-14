#include "MapGenerator.h"
#include <algorithm>
#include "PolygonPointSorter.h"
#include <iostream>
#include <list>


MapGenerator::MapGenerator()
{
}

const std::vector<sf::Vector2i>& MapGenerator::generate()
{
	PerlinNoise::SetupPerlinNoise(&fNoiseSeed2D, &fPerlinNoise2D, ARRAY_SIZE, ARRAY_SIZE);

	PerlinNoise::PerlinNoise2D(ARRAY_SIZE, ARRAY_SIZE, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);

	matrix.clear();
	
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		matrix.push_back(std::vector<CellType>());
		for (size_t j = 0; j < ARRAY_SIZE; j++)
		{
			matrix[i].push_back(WATER);
			int cellValue = (int)(fPerlinNoise2D[j*ARRAY_SIZE + i] * 12.0f);
			switch (cellValue)
			{
			case 9:
				matrix[i][j] = BEACH;
				walls.push_back(sf::Vector2i(i, j));
				break;
			case 10:
			case 11:
			case 12:
				matrix[i][j] = ISLAND;
				walls.push_back(sf::Vector2i(i, j));

				break;
			default:
				matrix[i][j] = WATER;
				break;
			}
		}
	}
	return walls;


}

const std::vector<sf::Vector2i>& MapGenerator::getWalls()
{
	return walls;
}

MapGenerator::~MapGenerator()
{
}
