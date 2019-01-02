#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "State.h"
#include "DEFINITIONS.h"
#include <string>
#include <iostream>

#include "Ship.h"
#include "ConcaveShape.h"

class GameState : public State
{
public:
	GameState(GameDataRef data);
	~GameState() {}

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;
	sf::View gameView;
	sf::Clock _clock;

	sf::Sprite _background;
	sf::Text velocity;
	sf::Text rotation;
	sf::Text position;
	sf::Text angle;
	Ship ship;

	sf::Vector2i lastMousePosition;
	bool mouseLeftClicked;
	float zoomFactor;

	ConcaveShape shape;

	float *fNoiseSeed2D = nullptr;
	float *fPerlinNoise2D = nullptr;
	int arraySize = 512;
	int nOctaveCount = 5;
	float fScalingBias = 0.4f;

	sf::VertexArray vertices;

	sf::Clock fpsClock;



};

