#pragma once
#include "State.h"
#include "Game.h"
#include "MapGenerator.h"
#include "MainMenuState.h"
class EditorState :
	public State
{
public:
	EditorState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	~EditorState();

private:
	GameDataRef _data;

	sf::View gameView;
	sf::Clock _clock;

	sf::RectangleShape _background;


	sf::Vector2i lastMousePosition;
	bool mouseLeftClicked;
	float zoomFactor;

	MapGenerator mapGenerator;

	sf::VertexArray vertices;
	sf::Clock fpsClock;

	std::vector<sf::RectangleShape> walls;
};

