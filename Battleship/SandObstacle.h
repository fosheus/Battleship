#pragma once
#include "Obstacle.h"
class SandObstacle :
	public Obstacle
{
public:
	SandObstacle(sf::Vector2f position, sf::Vector2f size);
	~SandObstacle();

	// Hérité via Obstacle
	virtual void resolveCollision(ICollidable & visitor, const CollisionResponse & collisionResponse) override;
	virtual void resolveCollisionWithShip(Ship & ship, const CollisionResponse & collisionResponse) override;
};

