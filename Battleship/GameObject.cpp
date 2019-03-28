#include "GameObject.h"


GameObject::GameObject()
{
	angle = 0;
	setPosition(sf::Vector2f(0, 0));
	
	acceleration = 0.2f;
	maxVelocity = 100.0f;

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

	
	position.x = position.x + velocity * cos(angle*3.14159 / 180.0f)*multiplier;
	position.y= position.y + velocity * sin(angle*3.14159 / 180.0f)*multiplier;
	
	
}

void GameObject::addVelocity(float velocityOffset)
{
	
	targetVelocity += velocityOffset;
	if (targetVelocity < 0.0f && targetVelocity < -maxVelocity) {
		targetVelocity = -maxVelocity;
	}
	if (targetVelocity > 0.0f && targetVelocity > maxVelocity) {
		targetVelocity = maxVelocity;
	}
}


void GameObject::setVelocity(float velocity)
{
	this->velocity = velocity;
	if (velocity < 0 && velocity < -maxVelocity) {
		velocity = -maxVelocity;
	}
	if (velocity > 0 && velocity > maxVelocity) {
		velocity = maxVelocity;
	}
}

void GameObject::setMaxVelocity(float maxVelocity)
{
	this->maxVelocity = maxVelocity;
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



void GameObject::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;
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

float GameObject::getMaxVelocity()
{
	return maxVelocity;
}

sf::Vector2f GameObject::getPosition()
{
	return position;
}

sf::Vector2f GameObject::getVelocityVector()
{
	return sf::Vector2f(std::cos(angle*M_PI / 180.0f), std::sin(angle*M_PI / 180.0f));
}



GameObject::~GameObject()
{
}
