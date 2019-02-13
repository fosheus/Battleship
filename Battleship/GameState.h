#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "State.h"
#include "DEFINITIONS.h"
#include <string>
#include <iostream>

#include "Ship.h"
#include "ConcaveShape.h"
#include "MapGenerator.h"

class GameState : public State
{
public:
	GameState(GameDataRef data);
	~GameState() {}

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private :
	friend void triangulatePolygon(ConcaveShape& shape, int i, int size);
private:
	GameDataRef _data;
	sf::View gameView;
	sf::Clock _clock;

	sf::RectangleShape _background;
	sf::Text velocity;
	sf::Text rotation;
	sf::Text position;
	sf::Text angle;
	Ship ship;

	sf::Vector2i lastMousePosition;
	bool mouseLeftClicked;
	float zoomFactor;

	ConcaveShape shape;
	std::vector<ConcaveShape> islands;
	std::vector<sf::Thread*> threads;

	std::vector<ConcaveShape> beaches;
	std::vector<sf::Vector2f> points;

	MapGenerator mapGenerator;

	sf::VertexArray vertices;

	sf::Clock fpsClock;



};

