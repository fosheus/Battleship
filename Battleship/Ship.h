#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "GameObject.h"
class Ship : public GameObject
{
public:
	Ship();


	void update(float multiplier);
	void render(sf::RenderTarget* target);

	sf::FloatRect getGlobalBounds();
	std::vector<sf::Vector2f> getPoints();
	void addRotation(float rotationOffset);
	void setRotation(float rotation);
	float getCurrentRotation();
	float getTargetRotation();
	void decelerate(float decelerateValue, float maxVelocity, float multiplier);


	//Accessors
	virtual void addVelocity(float velocityOffset);
	virtual void setVelocity(float velocity);
	virtual void setAcceleration(float acceleration);
	virtual void setMaxRotation(float maxRotation);
	virtual void setMaxVelocity(float maxVelocity);
	virtual void setBlocked(bool blocked);
	virtual void setSize(sf::Vector2f size,sf::Vector2f originOffset);

	virtual float getCurrentVelocity();
	virtual float getTargetVelocity();
	virtual float getAcceleration();
	virtual float getMaxRotation();
	virtual float getMaxVelocity();
	virtual bool isBlocked();
	virtual sf::Vector2f getSize();

	

	~Ship();

private:
	void updateShape();

private:
	sf::RectangleShape shape;
	const float ROTATION_ACCELERATION = 5.0f;
	const float VELOCITY_RATIO = 10.0f;
	float targetRotation;
	float rotation;
	float maxRotation;
	bool blocked;
	float blockedTargetVelocity;

};

