#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "GameObject.h"
#include "ICollidable.h"
class Ship : public GameObject ,public ICollidable
{
public:
	Ship();


	void update(float multiplier);
	void render(sf::RenderTarget* target);

	virtual sf::FloatRect getGlobalBounds();
	virtual std::vector<sf::Vector2f> getPoints();
	virtual void resolveCollision(ICollidable & visitor, const CollisionResponse& collisionResponse) override;

	void addRotation(float rotationOffset);
	void setRotation(float rotation);
	float getCurrentRotation();
	float getTargetRotation();
	void decelerate(float decelerateValue, float maxVelocity, float multiplier);
	void rewindMovement(float dt);

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

	void setColor(sf::Color color) { shape.setFillColor(color); }
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


	// Hérité via ICollidable
	

	virtual void resolveCollisionWithShip(Ship & ship, const CollisionResponse& collisionResponse) override;

	virtual void resolveCollisionWithIsland(IslandObstacle & island, const CollisionResponse& collisionResponse) override;

	virtual void resolveCollisionWithBeach(SandObstacle & beach, const CollisionResponse& collisionResponse) override;


	// Hérité via ICollidable
	virtual sf::Vector2f getVelocityVector() override;

};

