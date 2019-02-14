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
	void initGUI();
	void initEntities();
	void initWalls();
	int pnpoly(std::vector<sf::Vector2f>& points,sf::Vector2f testPoint);
	bool rectanglesCollide(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2);
	void manageInputGameView(sf::Event& event);
	void manageInputShipMouvement(sf::Event &event);

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

	MapGenerator mapGenerator;

	sf::VertexArray vertices;
	sf::RenderTexture wallsTexture;
	sf::Clock fpsClock;

	std::vector<sf::RectangleShape> walls;


};

