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
	static bool rotatedCollisionDetection(sf::RectangleShape a, sf::RectangleShape b);

	~Utils();
};

