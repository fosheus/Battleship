#include "Ship.h"
#include <iostream>


Ship::Ship()
{
	maxRotation = 180.0f;
	rotation = 0.0f;
	targetRotation = 0.0f;
	blocked = false;
	shape.setFillColor(sf::Color::Green);
	setSize(sf::Vector2f(201, 31), sf::Vector2f(100, 15));
}
void Ship::update(float multiplier) {
	GameObject::update(multiplier);
	if (getCurrentVelocity()>0.0f) {
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
		
		addAngle(rotation * getCurrentVelocity() / getMaxVelocity() * multiplier);
	}
	

	updateShape();
}

void Ship::render(sf::RenderTarget * target)
{
	if (target) {
		target->draw(shape);
	}
}

void Ship::updateShape()
{
	shape.setPosition(getPosition());
	shape.setRotation(getAngle());
}

sf::FloatRect Ship::getGlobalBounds()
{
	return shape.getGlobalBounds();
}

std::vector<sf::Vector2f> Ship::getPoints()
{
	
	std::vector<sf::Vector2f> points;
	
	for (int i = 0; i < shape.getPointCount(); i++) {
		points.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
	}
	return points;
	
}

void Ship::addRotation(float rotationOffset)
{
	this->targetRotation += rotationOffset;
	if (targetRotation < 0 && targetRotation < -maxRotation) {
		targetRotation = -maxRotation;
	}
	if (targetRotation > 0 && targetRotation > maxRotation) {
		targetRotation = maxRotation;
	}
}

void Ship::setRotation(float rotation)
{
	this->targetRotation = rotation;
	if (targetRotation < 0 && targetRotation < -maxRotation) {
		targetRotation = -maxRotation;
	}
	if (targetRotation > 0 && targetRotation > maxRotation) {
		targetRotation = maxRotation;
	}
}

float Ship::getCurrentRotation()
{
	return rotation;
}

float Ship::getTargetRotation()
{
	return targetRotation;
}

void Ship::decelerate(float decelerateValue, float maxVelocity,float multiplier)
{
	maxVelocity = std::abs(maxVelocity);
	if (getCurrentVelocity() > 0 && getCurrentVelocity() > maxVelocity) {
			setVelocity(getCurrentVelocity() - decelerateValue * multiplier);
	}
	else if (getCurrentVelocity() <0 && getCurrentVelocity() <-maxVelocity)  {
		setVelocity(getCurrentVelocity() + decelerateValue * multiplier);
	}
}

void Ship::addVelocity(float velocityOffset)
{
	GameObject::addVelocity(velocityOffset*VELOCITY_RATIO);
}

void Ship::setVelocity(float velocity)
{
	GameObject::setVelocity(velocity*VELOCITY_RATIO);
}

void Ship::setAcceleration(float acceleration) {
	GameObject::setAcceleration(acceleration*VELOCITY_RATIO);
}

void Ship::setMaxRotation(float maxRotation)
{
	this->maxRotation = maxRotation;
}

void Ship::setMaxVelocity(float maxVelocity)
{
	GameObject::setMaxVelocity(maxVelocity*VELOCITY_RATIO);
}

void Ship::setBlocked(bool blocked)
{
	this->blocked = blocked;
}

void Ship::setSize(sf::Vector2f size,sf::Vector2f originOffset)
{
	shape.setSize(size);
	shape.setOrigin(originOffset);
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

float Ship::getMaxRotation()
{
	return maxRotation;
}

float Ship::getMaxVelocity()
{
	return GameObject::getMaxVelocity()/VELOCITY_RATIO;
}

bool Ship::isBlocked()
{
	return blocked;
}

sf::Vector2f Ship::getSize()
{
	return shape.getSize();
}

Ship::~Ship()
{
}


