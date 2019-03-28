#pragma once
class Ship;
class IslandObstacle;
class SandObstacle;

#include <vector>
#include "SFML/Graphics.hpp"
class ICollidable
{
public:

	virtual std::vector<sf::Vector2f> getPoints()=0;
	virtual void resolveCollision(ICollidable& visitor) = 0;


	virtual void resolveCollisionWithShip(Ship& ship) = 0;
	virtual void resolveCollisionWithIsland(IslandObstacle& ship) = 0;
	virtual void resolveCollisionWithBeach(SandObstacle& ship) = 0;
};

