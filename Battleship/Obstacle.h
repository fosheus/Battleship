#pragma once
#include "GameObject.h"
#include "ICollidable.h"
#include <vector>
class Obstacle : public GameObject, public ICollidable
{
public:
	Obstacle(bool mouvable,sf::Vector2f position, sf::Vector2f size);
	sf::FloatRect getGlobalBounds();
	std::vector<sf::Vector2f> getPoints() ;
	sf::Vector2f getSize();
	virtual ~Obstacle()=0;

private :
	bool mouvable;
	sf::Vector2f size;

	// Hérité via ICollidable
	virtual void resolveCollision(ICollidable & visitor) override ;
	virtual void resolveCollisionWithShip(Ship & ship) override ;
	virtual void resolveCollisionWithIsland(IslandObstacle & island) override ;
	virtual void resolveCollisionWithBeach(SandObstacle & ship) override;
};

