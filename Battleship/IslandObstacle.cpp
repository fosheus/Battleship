#include "IslandObstacle.h"



IslandObstacle::IslandObstacle(sf::Vector2f position, sf::Vector2f size) : Obstacle(false,position,size)
{
}

IslandObstacle::~IslandObstacle()
{
}


void IslandObstacle::resolveCollision(ICollidable & visitor, const CollisionResponse & collisionResponse)
{
	visitor.resolveCollisionWithIsland(*this,collisionResponse);
}

void IslandObstacle::resolveCollisionWithShip(Ship & ship, const CollisionResponse & collisionResponse)
{
	ship.setPosition(ship.getPosition() + collisionResponse.collisionVector);
}
