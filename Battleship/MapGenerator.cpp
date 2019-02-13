#include "MapGenerator.h"
#include <algorithm>
#include "PolygonPointSorter.h"
#include <iostream>
#include <list>

void MapGenerator::fillIslandsAndBeaches()
{
	int **visitedMatrix;
	visitedMatrix = new int*[arraySize];
	for (size_t i = 0; i < arraySize; i++)
	{
		visitedMatrix[i] = new int[arraySize];
		for (size_t j = 0; j < arraySize; j++)
		{
			visitedMatrix[i][j] = 0;
		}
	}

	std::vector<std::list<sf::Vector2i>> islands;
	for (size_t i = 0; i < arraySize; i++)
	{
		for (size_t j = 0; j < arraySize; j++)
		{
			sf::Vector2i current(i, j);
			if (matrix[i][j] == BEACH && isPointAnEdge(current, WATER)) {
				bool createList = true;
				for (int k = 0; k < islands.size(); k++) {
					sf::Vector2i& front = islands[k].front();
					sf::Vector2i& back = islands[k].back();
					std::list<sf::Vector2i>& island = islands[k];
					if (areNeighbors(front, current)) {
						/*if (island.size() >= 3) {
							sf::Vector2i second = *std::next(island.begin());
							if (areNeighbors(second, current)) {
								sf::Vector2i f = front;
								island.pop_front();
								island.push_front(current);
								island.push_front(f);
								createList = false;
								continue;
							} 
						}
						 */
						island.push_front(current);
						createList = false;
						continue;
						
					
					}
					else if (island.size() >=2 && areNeighbors(back, current)) {
						/*if (island.size() >= 4) {
							sf::Vector2i beforeLast = *std::prev(island.end(),2);
							if (areNeighbors(beforeLast, current)) {
								sf::Vector2i b = back;
								island.pop_back();
								island.push_back(current);
								island.push_back(b);
								createList = false;
								continue;
							}

						}*/
					
						island.push_back(current);
						createList = false;
						continue;
						

					}
					
				}

				if (createList) {
					islands.push_back(std::list<sf::Vector2i>());
					islands[islands.size() - 1].push_back(current);
				}
			}
		}
	}
	
	for (auto it1 = islands.begin(); it1 != islands.end();) {
		if (it1->size() == 0) {
			it1++;
			continue;
		}
		for (auto it2 = islands.begin(); it2 != islands.end();) {
			if (it1 == it2 || it2->size() == 0) {
				it2++;
				continue;
			}
			

			if (it1->front() == it2->front()) {
				it1->reverse();
				it1->pop_back();
				it1->splice(it1->end(), *it2);
			}
			else if (it1->front() == it2->back()) {
				it2->pop_back();
				it2->splice(it2->end(), *it1);
				break;
			}
			else if (it1->back() == it2->front()) {
				it1->pop_back();
				it1->splice(it1->end(), *it2);
			}
			else if (it1->back() == it2->back()) {
				it2->reverse();
				it1->pop_back();
				it1->splice(it1->end(), *it2);
			}
			++it2;
		}
		++it1;


	}
	for (auto it = islands.begin(); it != islands.end();) {
		if (it->size() == 0) {
			it = islands.erase(it);
		}
		else {
			++it;
		}
	}

	for (int i = 0;i<islands.size();i++) {
		this->islands.push_back(std::vector<sf::Vector2i>());
		for (auto it = islands[i].begin();it != islands[i].end();++it) {
			this->islands[i].push_back(*it);
		}
	}
	
	for (int i = 0; i < arraySize; i++) {
		delete[] visitedMatrix[i];
	}
	delete[] visitedMatrix;
}

bool MapGenerator::areNeighbors(sf::Vector2i p1, sf::Vector2i p2) {

	float dist = std::sqrt(std::pow(((float)p1.x - (float)p2.x),2.0f) + std::pow(((float)p1.y - (float)p2.y),2.0f));
	return  dist <2.0f;
}


int MapGenerator::isPositionOfType(sf::Vector2i p,CellType type) {
	if (p.x < 0 || p.x >= arraySize || p.y < 0 || p.y >= arraySize) {
		return -1;
	}
	if (matrix[p.x][p.y] == type) {
		return 1;
	}
	return 0;
}

void MapGenerator::addAdjToSameTree(int x, int y, int ** visitedMatrix, int currentTree)
{
	if (!visitedMatrix[x][y]) {
		int cellValue = x  + y * arraySize;
		islandsAndBeaches[currentTree].push_back(sf::Vector2i(x, y));
		visitedMatrix[x][y] = 1;
		for (sf::Vector2i var : getNeighboursOfSameType(sf::Vector2i(x, y)))
		{
			addAdjToSameTree(var.x, var.y, visitedMatrix, currentTree);
		}
	}
}

void MapGenerator::addAdjEdgeToSameTree(int x, int y, int ** visitedMatrix, int currentTree)
{

	if (!visitedMatrix[x][y]) {

		std::vector<sf::Vector2i>& neighbours = getStarEdgeNeighboorOfSameType(sf::Vector2i(x, y));
		if (neighbours.size() == 1) {
			std::reverse(islandsAndBeaches[currentTree].begin(), islandsAndBeaches[currentTree].end());
		}else if(isPointAnEdge(sf::Vector2i(x, y), WATER)) {
			islandsAndBeaches[currentTree].push_back(sf::Vector2i(x, y));
		}
		visitedMatrix[x][y] = 1;
		
		for (sf::Vector2i var : neighbours)
		{
			addAdjEdgeToSameTree(var.x, var.y, visitedMatrix, currentTree);
		}
	}
}

std::vector<sf::Vector2i> MapGenerator::getStarEdgeNeighboorOfSameType(sf::Vector2i point) {
	std::vector<sf::Vector2i> tmpNeighbours;
	std::vector<sf::Vector2i> neighbours;

	tmpNeighbours.push_back(sf::Vector2i(-1, 0));
	tmpNeighbours.push_back(sf::Vector2i(0, 1));
	tmpNeighbours.push_back(sf::Vector2i(1, 0));
	tmpNeighbours.push_back(sf::Vector2i(0, -1));
	tmpNeighbours.push_back(sf::Vector2i(-1, 1));
	tmpNeighbours.push_back(sf::Vector2i(1, 1));
	tmpNeighbours.push_back(sf::Vector2i(1, -1));
	tmpNeighbours.push_back(sf::Vector2i(-1, -1));
	for (size_t i = 0; i < tmpNeighbours.size(); i++)
	{
		int checkX = point.x + tmpNeighbours[i].x;
		int checkY = point.y + tmpNeighbours[i].y;

		if (isPositionOfType(sf::Vector2i(checkX, checkY), (CellType)matrix[point.x][point.y]) == 1) {
			if (isPointAnEdge(sf::Vector2i(checkX, checkY), WATER)) {
				neighbours.push_back(sf::Vector2i(checkX, checkY));
			}
		}
	}
	return neighbours;
}

std::vector<sf::Vector2i> MapGenerator::getNeighboursOfSameType(sf::Vector2i point)
{
	std::vector<sf::Vector2i> tmpNeighbours;
	std::vector<sf::Vector2i> neighbours;

	tmpNeighbours.push_back(sf::Vector2i(-1, 0));
	tmpNeighbours.push_back(sf::Vector2i(-1, 1));
	tmpNeighbours.push_back(sf::Vector2i(0, 1));
	tmpNeighbours.push_back(sf::Vector2i(1, 1));
	tmpNeighbours.push_back(sf::Vector2i(1, 0));
	tmpNeighbours.push_back(sf::Vector2i(1, -1));
	tmpNeighbours.push_back(sf::Vector2i(0, -1));
	tmpNeighbours.push_back(sf::Vector2i(-1, -1));

	for (size_t i = 0; i < tmpNeighbours.size(); i++)
	{
		int checkX = point.x + tmpNeighbours[i].x;
		int checkY = point.y + tmpNeighbours[i].y;

		if (isPositionOfType(sf::Vector2i(checkX, checkY),(CellType)matrix[point.x ][point.y]) == 1) {
			neighbours.push_back(sf::Vector2i(checkX, checkY));
		}
	}
	return neighbours;
}


std::vector<sf::Vector2i> MapGenerator::getNeighboursCross(sf::Vector2i point)
{
	std::vector<sf::Vector2i> tmpNeighbours;
	std::vector<sf::Vector2i> neighbours;

	tmpNeighbours.push_back(sf::Vector2i(0, -1));
	tmpNeighbours.push_back(sf::Vector2i(-1, 0));
	tmpNeighbours.push_back(sf::Vector2i(1, 0));
	tmpNeighbours.push_back(sf::Vector2i(0, 1));
	for (size_t i = 0; i < tmpNeighbours.size(); i++)
	{
		int checkX = point.x + tmpNeighbours[i].x;
		int checkY = point.y + tmpNeighbours[i].y;

		if (isPositionInRange(sf::Vector2i(checkX, checkY))) {
			neighbours.push_back(sf::Vector2i(checkX, checkY));
		}
	}
	return neighbours;
}

MapGenerator::MapGenerator()
{
}

void MapGenerator::generate()
{
	PerlinNoise::SetupPerlinNoise(&fNoiseSeed2D, &fPerlinNoise2D, arraySize, arraySize);

	PerlinNoise::PerlinNoise2D(arraySize, arraySize, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);

	matrix.clear();
	islandsAndBeaches.clear();
	islands.clear();
	beaches.clear();
	for (size_t i = 0; i < arraySize; i++)
	{
		matrix.push_back(std::vector<CellType>());
		for (size_t j = 0; j < arraySize; j++)
		{
			matrix[i].push_back(WATER);
			int cellValue = (int)(fPerlinNoise2D[j*arraySize + i] * 12.0f);
			switch (cellValue)
			{
			case 9:
				matrix[i][j] = BEACH;
				break;
			case 10:
			case 11:
			case 12:
				matrix[i][j] = ISLAND;
				break;
			default:
				matrix[i][j] = WATER;
				break;
			}
		}
	}
	fillIslandsAndBeaches();

	for (size_t i = 0; i < islandsAndBeaches.size(); i++)
	{
		if (islandsAndBeaches[i].size() < 20) {
			islandsAndBeaches[i].clear();
		}
		else {
			if (matrix[islandsAndBeaches[i][0].x][islandsAndBeaches[i][0].y] == BEACH) {
				beaches.push_back(islandsAndBeaches[i]);
				std::vector<sf::Vector2i>& current= beaches[beaches.size() - 1];
				int i = 0;
				for (auto it = current.begin();it!=current.end()&&i<current.size();) {
					float distA = 0.0f;
					float distB = 0.0f;
					if (i > 0) {
						float distA = sqrt((it->x - (it - 1)->x)*(it->x - (it - 1)->x) - (it->y - (it - 1)->y)*(it->y - (it - 1)->y));
					}
					if (i != current.size() - 1) {
						float distB = sqrt((it->x - (it + 1)->x)*(it->x - (it + 1)->x) - (it->y - (it + 1)->y)*(it->y - (it + 1)->y));
					}
					if (distA>=2 || distB>=2) {
						it = current.erase(it);
					}
					else {
						it++;
						
						
					}
					i++;
					
				}
			}
		}/*
			//get center of the polygon
			sf::Vector2i center = compute2DPolygonCentroid(islandsAndBeaches[i]);

			//Get all edge point of the polygon
			std::vector<sf::Vector2i> tmp;
			CellType type;
			switch (matrix[islandsAndBeaches[i][0].x][islandsAndBeaches[i][0].y])
			{
			case BEACH:
				type = WATER;
				break;
			case ISLAND:
				type = BEACH;
				break;
			default:
				islandsAndBeaches[i].clear();
				continue;
			}
			for (size_t j = 0; j < islandsAndBeaches[i].size(); j++)
			{
				if (isPointAnEdge(islandsAndBeaches[i][j],type)) {
					tmp.push_back(islandsAndBeaches[i][j]);
				}
			}


			//create concave hull from set of points representing the edge
			/*TODO
			std::vector<sf::Vector2i> concaveHull;
			if (tmp.size() > 2) {
				int i = 1;
				sf::Vector2i startpoint = tmp[0];
				sf::Vector2i currentPoint = startpoint;
				concaveHull.push_back(startpoint);
				do {
					std::cout << "current : " << currentPoint.x << " : " << currentPoint.y << std::endl;
					sf::Vector2i selectedPoint(-1, -1);
					float greaterAngle = -1.0f;
					std::vector<sf::Vector2i> neighbours = getNeighboursOfSameType(currentPoint);
					for (sf::Vector2i p : neighbours) {
						std::cout << "neighboor : " << p.x << " : " << p.y;
						if (isPointAnEdge(p, type) == 1 && (std::find(concaveHull.begin(),concaveHull.end(),p)==concaveHull.end()) ) {
								float angle = (float)std::atan2(p.y - currentPoint.y, p.x - currentPoint.x)*180.0f/-3.14159265359f;
								if (angle < 0) {
									angle += 360.0f;
								}
								if (angle > greaterAngle) {
									greaterAngle = angle;
									selectedPoint = p;
								}
								std::cout << "  angle : " << angle;

						}
					std::cout << std::endl;
					}
					if (selectedPoint.x != -1 && selectedPoint.y != -1) {
						concaveHull.push_back(selectedPoint);
						currentPoint = selectedPoint;
						i++;
					}
					else {
						break;
					}

				} while (currentPoint != startpoint && i<tmp.size());

				if (type == WATER) {
					beaches.push_back(concaveHull);
				}
				else if (type == BEACH) {
					islands.push_back(concaveHull);
				}
			}
			*/

	}

}



bool MapGenerator::isPointAnEdge(sf::Vector2i point,CellType type) {
	std::vector<sf::Vector2i> neighbours = getNeighboursCross(point);
	if (point.x == 0 || point.y == 0 || point.x == arraySize - 1 || point.y == arraySize - 1) {
		return true;
	}
	for (sf::Vector2i p : neighbours) {
		if (isPositionOfType(p, type)==1) {
			return true;
		}
	}
	return false;
}

bool MapGenerator::isPositionInRange(sf::Vector2i p)
{
	if (p.x < 0 || p.x >= arraySize || p.y < 0 || p.y >= arraySize) {
		return false;
	}
	return true;
}



sf::Vector2i compute2DPolygonCentroid(const std::vector<sf::Vector2i> &vertices)
{
	sf::Vector2i centroid = { 0, 0 };
	double signedArea = 0.0;
	double x0 = 0.0; // Current vertex X
	double y0 = 0.0; // Current vertex Y
	double x1 = 0.0; // Next vertex X
	double y1 = 0.0; // Next vertex Y
	double a = 0.0;  // Partial signed area

	// For all vertices except last
	int i = 0;
	for (i = 0; i < vertices.size() - 1; ++i)
	{
		x0 = vertices[i].x;
		y0 = vertices[i].y;
		x1 = vertices[i + 1].x;
		y1 = vertices[i + 1].y;
		a = x0 * y1 - x1 * y0;
		signedArea += a;
		centroid.x += (x0 + x1)*a;
		centroid.y += (y0 + y1)*a;
	}

	// Do last vertex separately to avoid performing an expensive
	// modulus operation in each iteration.
	x0 = vertices[i].x;
	y0 = vertices[i].y;
	x1 = vertices[0].x;
	y1 = vertices[0].y;
	a = x0 * y1 - x1 * y0;
	signedArea += a;
	centroid.x += (x0 + x1)*a;
	centroid.y += (y0 + y1)*a;

	signedArea *= 0.5;
	centroid.x /= (6.0*signedArea);
	centroid.y /= (6.0*signedArea);

	return centroid;
}

MapGenerator::~MapGenerator()
{
}
