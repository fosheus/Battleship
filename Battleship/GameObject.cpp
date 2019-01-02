#include "GameObject.h"


GameObject::GameObject()
{
	angle = 0;
	position = sf::Vector2f(0, 0);
	acceleration = 0.2f;

}

void GameObject::update(float multiplier)
{
	
	if (targetVelocity > velocity) {
		velocity += acceleration*multiplier;
		if (targetVelocity < velocity) {
			velocity = targetVelocity;
		}
	}
	if (targetVelocity < velocity) {
		velocity -= acceleration *multiplier;
		if (targetVelocity > velocity) {
			velocity = targetVelocity;
		}
	}

	
	position.x = position.x + velocity * cos(angle*3.14159 / 180)*multiplier;
	position.y = position.y + velocity * sin(angle*3.14159 / 180)*multiplier;
	
	
}

void GameObject::addVelocity(float velocityOffset)
{
	targetVelocity += velocityOffset;
}


void GameObject::setVelocity(float velocity)
{
	targetVelocity = velocity;
}



void GameObject::setAngle(float angle)
{
	this->angle = angle;
	if (this->angle < -180) this->angle = this->angle + 360;
	if (this->angle > 180) this->angle = this->angle - 360;
}

void GameObject::addAngle(float angleOffset)
{
	this->angle += angleOffset;
	if (this->angle < -180) this->angle = this->angle + 360;
	if (this->angle > 180) this->angle = this->angle - 360;
}

void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void GameObject::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

sf::Vector2f GameObject::getPosition()
{
	return position;
}

float GameObject::getCurrentVelocity()
{
	return velocity;
}

float GameObject::getTargetVelocity()
{
	return targetVelocity;
}

float GameObject::getAngle()
{
	return angle;
}

float GameObject::getAcceleration()
{
	return acceleration;
}


GameObject::~GameObject()
{
}
