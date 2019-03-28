#include "IslandObstacle.h"



IslandObstacle::IslandObstacle(sf::Vector2f position, sf::Vector2f size) : Obstacle(false,position,size)
{
}

IslandObstacle::~IslandObstacle()
{
}

void IslandObstacle::resolveCollision(ICollidable & visitor)
{
	visitor.resolveCollisionWithIsland(*this);
}

void IslandObstacle::resolveCollisionWithShip(Ship & ship)
{
	
}
