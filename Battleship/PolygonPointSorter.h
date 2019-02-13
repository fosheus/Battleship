#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
class PolygonPointSorter
{

private: sf::Vector2i center;
public:
	PolygonPointSorter(sf::Vector2i center);
	bool operator()(sf::Vector2i a, sf::Vector2i b);
	~PolygonPointSorter();
};

