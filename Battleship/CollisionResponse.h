#pragma once
#include <SFML/System/Vector2.hpp>

class CollisionResponse
{
public : 
	bool collision;
	sf::Vector2f collisionVector;
	sf::Vector2f m;
	sf::Vector2f m2;
public:
	CollisionResponse(bool collision=false, sf::Vector2f collisionVector=sf::Vector2f(0,0), sf::Vector2f m=sf::Vector2f(0,0), sf::Vector2f m2=sf::Vector2f(0,0));
	~CollisionResponse();
};

