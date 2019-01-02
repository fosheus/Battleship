#pragma once

#include <SFML/System/Vector2.hpp>
#include <math.h>

class GameObject
{
public:
	GameObject();
	virtual void update(float multiplier);
	virtual void addVelocity(float velocityOffset);
	virtual void setVelocity(float velocity);
	virtual void setAngle(float angle);
	virtual void addAngle(float angleOffset);
	virtual void setPosition(sf::Vector2f position);
	virtual void setAcceleration(float acceleration);

	virtual sf::Vector2f getPosition();
	virtual float getCurrentVelocity();
	virtual float getTargetVelocity();
	virtual float getAngle();
	virtual float getAcceleration();
	~GameObject();

private:
	sf::Vector2f position;
	float targetVelocity;
	float velocity;
	float angle;
	float acceleration;


};

