#pragma once
#include "Obstacle.h"
class IslandObstacle :
	public Obstacle
{
public:
	IslandObstacle(sf::Vector2f position, sf::Vector2f size);
	virtual ~IslandObstacle();
private:

	virtual void resolveCollision(ICollidable & visitor) override ;
	virtual void resolveCollisionWithShip(Ship & ship) override ;
};

