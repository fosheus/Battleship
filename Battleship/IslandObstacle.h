#pragma once
#include "Obstacle.h"
class IslandObstacle :
	public Obstacle
{
public:
	IslandObstacle(sf::Vector2f position, sf::Vector2f size);
	virtual ~IslandObstacle();
private:

	

	// Hérité via Obstacle
	virtual void resolveCollision(ICollidable & visitor, const CollisionResponse& collisionResponse) override;
	virtual void resolveCollisionWithShip(Ship & ship, const CollisionResponse& collisionResponse) override;

};

