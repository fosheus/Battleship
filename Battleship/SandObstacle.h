#pragma once
#include "Obstacle.h"
class SandObstacle :
	public Obstacle
{
public:
	SandObstacle(sf::Vector2f position, sf::Vector2f size);
	~SandObstacle();
};

