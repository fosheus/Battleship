#include "CollisionResponse.h"




CollisionResponse::CollisionResponse(bool collision, sf::Vector2f collisionVector):
	intersect(collision),collisionVector(collisionVector){
	
}

CollisionResponse::~CollisionResponse()
{
}
