#pragma once
#include <SFML/Graphics.hpp>
class Utils
{
public:
	Utils();
	static std::vector<sf::Vector2f> getPoints(sf::RectangleShape rect) {
		std::vector<sf::Vector2f> rectPoints;
		rectPoints.push_back(rect.getPoint(0) + rect.getPosition());
		rectPoints.push_back(rect.getPoint(2) + rect.getPosition());
		rectPoints.push_back(rect.getPoint(1) + rect.getPosition());
		rectPoints.push_back(rect.getPoint(3) + rect.getPosition());
		return rectPoints;
		
	}
	static sf::Vector2f normalize(sf::Vector2f vect) {
		float length = std::sqrt(vect.x*vect.x + vect.y*vect.y);
		return sf::Vector2f(vect.x / length, vect.y / length);
	}

	static float dotProduct(sf::Vector2f vect1, sf::Vector2f vect2) {
		return vect1.x*vect2.x + vect1.y*vect2.y;
	}

	static sf::Vector2f compute2DPolygonCentroid(const std::vector<sf::Vector2f> vertices)
	{
		sf::Vector2f centroid = { 0, 0 };
		double signedArea = 0.0;
		double x0 = 0.0; // Current vertex X
		double y0 = 0.0; // Current vertex Y
		double x1 = 0.0; // Next vertex X
		double y1 = 0.0; // Next vertex Y
		double a = 0.0;  // Partial signed area

		// For all vertices except last
		size_t i = 0;
		for (i = 0; i < vertices.size() - 1; ++i)
		{
			x0 = vertices[i].x;
			y0 = vertices[i].y;
			x1 = vertices[i + 1].x;
			y1 = vertices[i + 1].y;
			a = x0 * y1 - x1 * y0;
			signedArea += a;
			centroid.x += (x0 + x1)*a;
			centroid.y += (y0 + y1)*a;
		}

		// Do last vertex separately to avoid performing an expensive
		// modulus operation in each iteration.
		x0 = vertices[i].x;
		y0 = vertices[i].y;
		x1 = vertices[0].x;
		y1 = vertices[0].y;
		a = x0 * y1 - x1 * y0;
		signedArea += a;
		centroid.x += (x0 + x1)*a;
		centroid.y += (y0 + y1)*a;

		signedArea *= 0.5;
		centroid.x /= (6.0*signedArea);
		centroid.y /= (6.0*signedArea);

		return centroid;
	}


	static bool rotatedCollisionDetection(sf::RectangleShape a, sf::RectangleShape b);

	~Utils();
};

