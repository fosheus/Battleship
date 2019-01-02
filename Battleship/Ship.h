#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
class Ship : public GameObject
{
public:
	Ship();
	void update(float multiplier);
	void addRotation(float rotationOffset);
	void setRotation(float rotation);
	float getCurrentRotation();
	float getTargetRotation();

	virtual void addVelocity(float velocityOffset);
	virtual void setVelocity(float velocity);
	virtual void setAcceleration(float acceleration);

	virtual float getCurrentVelocity();
	virtual float getTargetVelocity();
	virtual float getAcceleration();

	~Ship();
private:

	const float ROTATION_ACCELERATION = 5.0f;
	const float VELOCITY_RATIO = 10.0f;
	float targetRotation;
	float rotation;

};

