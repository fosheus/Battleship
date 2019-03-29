#pragma once
class Ship;
class IslandObstacle;
class SandObstacle;

#include <vector>
#include "SFML/Graphics.hpp"
#include "CollisionResponse.h"
class ICollidable
{
public:
	virtual sf::FloatRect getGlobalBounds()=0;
	virtual std::vector<sf::Vector2f> getPoints()=0;
	virtual sf::Vector2f getVelocityVector() = 0;
	virtual void resolveCollision(ICollidable& visitor, const CollisionResponse& collisionResponse) = 0;


	virtual void resolveCollisionWithShip(Ship& ship, const CollisionResponse& collisionResponse) = 0;
	virtual void resolveCollisionWithIsland(IslandObstacle& island, const CollisionResponse& collisionResponse) = 0;
	virtual void resolveCollisionWithBeach(SandObstacle& beach, const CollisionResponse& collisionResponse) = 0;
};

