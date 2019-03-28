#include "Collider.h"



Collider::Collider()
{
}


Collider::~Collider()
{
}


CollisionResponse Collider::checkCollision(ICollidable& obj1, ICollidable& obj2)
{
	std::vector<sf::Vector2f> obj1Points = obj1.getPoints();
	std::vector<sf::Vector2f> obj2Points = obj2.getPoints();
	return polygonesCollide(obj1Points, obj2Points);

}



int Collider::pnpoly(std::vector<sf::Vector2f>& points, sf::Vector2f testPoint)
{

	int i, j, c = 0;
	for (i = 0, j = points.size() - 1; i < points.size(); j = i++) {
		if (((points[i].y > testPoint.y) != (points[j].y > testPoint.y)) &&
			(testPoint.x < (points[j].x - points[i].x) * (testPoint.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
			c = !c;
	}
	return c;

}

CollisionResponse Collider::polygonesCollide(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2) {
	for (int i = 0; i < rect2.size(); i++) {
		if (pnpoly(rect1, rect2[i]) != 0) {
			//return i;
			float minDist=FLT_MAX;
			
			sf::Vector2f collisionVector(0, 0);
			sf::Vector2f collisionVectorTmp(0, 0);
			sf::Vector2f M;
			sf::Vector2f M2;
			for (int j = 0; j < rect1.size(); j++) {
				sf::Vector2f m = rect2[i];
				sf::Vector2f a = rect1[j];
				sf::Vector2f b = rect1[(j + 1) % rect1.size()];
				float coefficientDirecteur = (b.y - a.y) / (b.x - a.x);
				float ordonnee = b.y - b.x*coefficientDirecteur;

				float coefficientDirecteur2 = -1 / coefficientDirecteur;
				float ordonnee2 = m.y - m.x*coefficientDirecteur2;

				float x = (ordonnee-ordonnee2)/ (coefficientDirecteur2 - coefficientDirecteur);
				float y = coefficientDirecteur2 * x - ordonnee2;
				collisionVectorTmp.x = m.x - x;
				collisionVectorTmp.y = m.y - y;

				float tmpDist = collisionVectorTmp.x*collisionVectorTmp.x + collisionVectorTmp.y*collisionVectorTmp.y;
				if (minDist > tmpDist) {
					minDist = tmpDist;
					collisionVector = collisionVectorTmp;
					M = m;
					M2 = sf::Vector2f(x,y);
				}
			}
			return CollisionResponse(true, collisionVector, M, M2);
		}
	}
	return CollisionResponse();
}