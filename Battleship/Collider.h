#pragma once
#include "ICollidable.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "CollisionResponse.h"
class Collider
{
public:
	Collider();
	~Collider();

	//functions
	static CollisionResponse checkCollision(ICollidable& obj1, ICollidable& obj2);
	static CollisionResponse polygonesCollide(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2);


private :
	static int pnpoly(std::vector<sf::Vector2f>& points, sf::Vector2f testPoint);
};

