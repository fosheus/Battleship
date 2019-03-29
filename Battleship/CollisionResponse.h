#pragma once
#include <SFML/System/Vector2.hpp>

class CollisionResponse
{
public : 
	bool willIntersect;
	bool intersect;
	sf::Vector2f collisionVector;
public:
	CollisionResponse(bool collision=false, sf::Vector2f collisionVector=sf::Vector2f(0,0));
	~CollisionResponse();
};

