#include "CollisionResponse.h"




CollisionResponse::CollisionResponse(bool collision, sf::Vector2f collisionVector, sf::Vector2f m, sf::Vector2f m2):
	intersect(collision),collisionVector(collisionVector),m(m),m2(m2)
{
	
}

CollisionResponse::~CollisionResponse()
{
}
