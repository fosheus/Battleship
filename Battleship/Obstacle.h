#pragma once
#include "GameObject.h"
#include "ICollidable.h"
#include <vector>
#include "Ship.h"
class Obstacle : public GameObject, public ICollidable
{
public:
	Obstacle(bool mouvable, sf::Vector2f position, sf::Vector2f size);
	sf::Vector2f getSize();
	virtual ~Obstacle() = 0;

private:
	bool mouvable;
	sf::Vector2f size;

	// Hérité via ICollidable
	virtual sf::FloatRect getGlobalBounds() override;
	virtual std::vector<sf::Vector2f> getPoints() override;
	virtual void resolveCollision(ICollidable & visitor, const CollisionResponse& collisionResponse) override = 0;
	virtual void resolveCollisionWithShip(Ship & ship, const CollisionResponse& collisionResponse) override = 0;
	virtual void resolveCollisionWithIsland(IslandObstacle & island, const CollisionResponse& collisionResponse) override {};
	virtual void resolveCollisionWithBeach(SandObstacle & beach, const CollisionResponse& collisionResponse) override  {};

	// Hérité via ICollidable
	virtual sf::Vector2f getVelocityVector() override;
};

