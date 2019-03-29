#include "SandObstacle.h"

SandObstacle::SandObstacle(sf::Vector2f position, sf::Vector2f size) : Obstacle(false, position,size)
{

}

SandObstacle::~SandObstacle()
{
}

void SandObstacle::resolveCollision(ICollidable & visitor, const CollisionResponse & collisionResponse)
{
	visitor.resolveCollisionWithBeach(*this, collisionResponse);
}

void SandObstacle::resolveCollisionWithShip(Ship & ship, const CollisionResponse & collisionResponse)
{
	ship.setBlocked(true);
}
