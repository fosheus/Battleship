#include "Obstacle.h"


Obstacle::Obstacle(bool mouvable, sf::Vector2f position, sf::Vector2f size) : mouvable(mouvable),size(size)
{
	setPosition(position);
	setAcceleration(0);
	setAngle(0);
	this->setMaxVelocity(0);
	this->setVelocity(0);
	
}

sf::FloatRect Obstacle::getGlobalBounds()
{
	return sf::FloatRect(getPosition(), getSize());
}

std::vector<sf::Vector2f> Obstacle::getPoints()
{
	std::vector<sf::Vector2f> points;
	points.push_back(getPosition());
	points.push_back(getPosition()+sf::Vector2f(size.x,0));
	points.push_back(getPosition()+getSize());
	points.push_back(getPosition()+sf::Vector2f(0,size.y));

	return points;
}

sf::Vector2f Obstacle::getVelocityVector()
{
	return sf::Vector2f(0,0);
}

sf::Vector2f Obstacle::getSize()
{
	return size;
}

Obstacle::~Obstacle()
{
}

