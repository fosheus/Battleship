#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <math.h>

class GameObject 
{
public:
	GameObject();
	virtual void update(float multiplier);
	virtual void addVelocity(float velocityOffset);
	virtual void setVelocity(float velocity);
	virtual void setMaxVelocity(float maxVelocity);
	virtual void setAngle(float angle);
	virtual void addAngle(float angleOffset);
	virtual void setAcceleration(float acceleration);
	virtual void setPosition(sf::Vector2f position);


	virtual float getCurrentVelocity();
	virtual float getTargetVelocity();
	virtual float getAngle();
	virtual float getAcceleration();
	virtual float getMaxVelocity();
	virtual sf::Vector2f getPosition();

	~GameObject();

private:
	sf::Vector2f position;
	float targetVelocity;
	float velocity;
	float angle;
	float acceleration;
	float maxVelocity;
	


};

