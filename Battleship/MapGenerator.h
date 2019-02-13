#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "PerlinNoise.h"
class MapGenerator
{
public :
	enum CellType {
		WATER,
		BEACH,
		ISLAND
	};

private :
	friend sf::Vector2i compute2DPolygonCentroid(const std::vector<sf::Vector2i> &vertices);

private:
	float *fNoiseSeed2D = nullptr;
	float *fPerlinNoise2D = nullptr;
	int arraySize = 256;
	int nOctaveCount = 5;
	float fScalingBias = 0.4f;

	std::vector<std::vector<CellType>> matrix;
	std::vector<std::vector<sf::Vector2i>> islandsAndBeaches;
	

	void fillIslandsAndBeaches();
	void addAdjToSameTree(int x, int y, int **visitedMatrix, int currentTree);
	void addAdjEdgeToSameTree(int x, int y, int **visitedMatrix, int currentTree);
	std::vector<sf::Vector2i> getStarEdgeNeighboorOfSameType(sf::Vector2i point);
	std::vector<sf::Vector2i> getNeighboursOfSameType(sf::Vector2i point);
	std::vector<sf::Vector2i> getNeighboursCross(sf::Vector2i point);
	bool areNeighbors(sf::Vector2i p1, sf::Vector2i p2);
public:
	MapGenerator();
	void generate();
	/**
	* Returns 1 if position is of type, 0 otherwise
	* if position not in range, returns -1
	*/
	int isPositionOfType(sf::Vector2i cell,CellType type);
	bool isPointAnEdge(sf::Vector2i,CellType type);
	bool isPositionInRange(sf::Vector2i point);
	~MapGenerator();

public :
	std::vector<std::vector<sf::Vector2i>> islands;
	std::vector<std::vector<sf::Vector2i>> beaches;
};

