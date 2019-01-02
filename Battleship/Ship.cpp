#include "Ship.h"



Ship::Ship()
{
}
void Ship::update(float multiplier) {
	GameObject::update(multiplier);
	if (getCurrentVelocity()) {
		if (targetRotation < rotation) {
			rotation -= ROTATION_ACCELERATION * multiplier;
			if (targetRotation > rotation) {
				rotation = targetRotation;
			}
		}
		if (targetRotation > rotation) {
			rotation += ROTATION_ACCELERATION * multiplier;
			if (targetRotation < rotation) {
				rotation = targetRotation;
			}
		}

		setAngle(getAngle() + rotation * multiplier);
	}
	
}

void Ship::addRotation(float rotationOffset)
{
	this->targetRotation += rotationOffset;
}

void Ship::setRotation(float rotation)
{
	this->targetRotation = rotation;
}

float Ship::getCurrentRotation()
{
	return rotation;
}

float Ship::getTargetRotation()
{
	return targetRotation;
}

void Ship::addVelocity(float velocityOffset)
{
	GameObject::addVelocity(velocityOffset*VELOCITY_RATIO);
}

void Ship::setVelocity(float velocity)
{
	GameObject::addVelocity(velocity*VELOCITY_RATIO);
}

void Ship::setAcceleration(float acceleration) {
	GameObject::setAcceleration(acceleration*VELOCITY_RATIO);
}


float Ship::getCurrentVelocity()
{
	return GameObject::getCurrentVelocity()/VELOCITY_RATIO;
}

float Ship::getTargetVelocity()
{
	return GameObject::getTargetVelocity() / VELOCITY_RATIO;
}

float Ship::getAcceleration()
{
	return GameObject::getAcceleration()/VELOCITY_RATIO;
}

Ship::~Ship()
{
}
