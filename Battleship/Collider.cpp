#include "Collider.h"
#include "Utils.h"

Collider::Collider()
{
}


Collider::~Collider()
{
}




CollisionResponse Collider::polygonCollision(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2, sf::Vector2f velocity)
{
	CollisionResponse result;
	result.intersect = true;
	result.willIntersect = true;

	int edgeCountA = rect1.size();
	int edgeCountB = rect2.size();
	float minIntervalDistance = FLT_MAX;;
	sf::Vector2f translationAxis;
	sf::Vector2f  edge;

	sf::Vector2f rect1Center = Utils::compute2DPolygonCentroid(rect1);
	sf::Vector2f rect2Center = Utils::compute2DPolygonCentroid(rect2);

	// Loop through all the edges of both polygons
	for (int edgeIndex = 0; edgeIndex < edgeCountA + edgeCountB; edgeIndex++) {
		if (edgeIndex < edgeCountA) {
			edge = rect1[edgeIndex];
		}
		else {
			edge = rect2[edgeIndex - edgeCountA];
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge
		sf::Vector2f axis(-edge.y, edge.x);
		axis = Utils::normalize(axis);
		
		// Find the projection of the polygon on the current axis
		float minA = 0; float minB = 0; float maxA = 0; float maxB = 0;
		projectPolygon(axis, rect1, minA,  maxA);
		projectPolygon(axis, rect2,  minB,  maxB);

		// Check if the polygon projections are currentlty intersecting
		if (intervalDistance(minA, maxA, minB, maxB) > 0)\
			result.intersect = false;

		// ===== 2. Now find if the polygons *will* intersect =====

		// Project the velocity on the current axis
		float velocityProjection = Utils::dotProduct(axis,velocity);

		// Get the projection of polygon A during the movement
		if (velocityProjection < 0) {
			minA += velocityProjection;
		}
		else {
			maxA += velocityProjection;
		}

		// Do the same test as above for the new projection
		float intDist = intervalDistance(minA, maxA, minB, maxB);
		if (intDist > 0) result.willIntersect = false;

		// If the polygons are not intersecting and won't intersect, exit the loop
		if (!result.intersect && !result.willIntersect) break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		intDist = std::abs(intDist);
		if (intDist < minIntervalDistance) {
			minIntervalDistance = intDist;
			translationAxis = axis;

			sf::Vector2f d = rect1Center - rect2Center;
			if (Utils::dotProduct(d,translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.willIntersect)
		result.collisionVector=translationAxis * minIntervalDistance;

	return result;
}
void Collider::projectPolygon(sf::Vector2f axis, std::vector<sf::Vector2f> polygon, float & min, float & max)
{

	float dp = Utils::dotProduct(axis,polygon[0]);
	min = dp;
	max = dp;
	for (int i = 0; i < polygon.size(); i++) {
		dp = Utils::dotProduct(polygon[i],axis);
		if (dp < min) {
			min = dp;
		}
		else {
			if (dp > max) {
				max = dp;
			}
		}
	}
}
float Collider::intervalDistance(float minA, float maxA, float minB, float maxB)
{
	if (minA < minB) {
		return minB - maxA;
	}
	else {
		return minA - maxB;
	}
}

CollisionResponse Collider::checkEntitiesCollision(ICollidable& obj1, ICollidable& obj2)
{
	std::vector<sf::Vector2f> obj1Points = obj1.getPoints();
	std::vector<sf::Vector2f> obj2Points = obj2.getPoints();
	return polygonesCollide(obj1Points, obj2Points);

}
CollisionResponse Collider::checkTerrainCollision(ICollidable& obj1, ICollidable& obj2)
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
				sf::Vector2f p1 = rect1[j];
				sf::Vector2f p2 = rect1[(j + 1) % rect1.size()];
				float a1 = p2.y - p1.y;
				float b1 = -(p2.x - p1.x);
				float c1 = -(a1*p1.x + b1 * p1.y);
				

				float a2 = -b1;
				float b2 = a1;
				float c2 = -(a2*m.x + b2 * m.y);


				double determinant = a1 * b2 - a2 * b1;
				double x=0.0f, y=0.0f;
				if (determinant != 0) {
					x = (c1*b2 - b1 * c2) / -determinant;
					y = (a1*c2 - c1 * a2) / -determinant;
				}
				

				collisionVectorTmp.x = m.x - x;
				collisionVectorTmp.y = m.y - y;

				float tmpDist = collisionVectorTmp.x*collisionVectorTmp.x + collisionVectorTmp.y*collisionVectorTmp.y;
				if (minDist > tmpDist && x >0 && y >0) {
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

