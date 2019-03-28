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
	static CollisionResponse checkTerrainCollision(ICollidable& obj1, ICollidable& obj2);
	static CollisionResponse checkEntitiesCollision(ICollidable& obj1, ICollidable& obj2);


	static CollisionResponse polygonCollision(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2, sf::Vector2f velocity);
	
	static CollisionResponse polygonesCollide(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2);


private :
	static void projectPolygon(sf::Vector2f axis, std::vector<sf::Vector2f> polygon, float& min, float& max);
	static float intervalDistance(float minA, float maxA, float minB, float maxB);
	
	static int pnpoly(std::vector<sf::Vector2f>& points, sf::Vector2f testPoint);
};

