#include "EditorState.h"



EditorState::EditorState(GameDataRef data) : _data(data)
{
}

void EditorState::Init()
{
	this->_background.setFillColor(sf::Color::Blue);
	this->_background.setSize(sf::Vector2f(ARRAY_SIZE * WALL_SIZE, ARRAY_SIZE * WALL_SIZE));

	gameView.setCenter(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	zoomFactor = 1.0f;

	/*std::vector<sf::Vector2i>& mapWalls = mapGenerator.generate();
	sf::RectangleShape r;
	r.setFillColor(sf::Color::Yellow);
	r.setSize(sf::Vector2f(WALL_SIZE, WALL_SIZE));
	for (sf::Vector2i wall : mapWalls) {
		r.setPosition(sf::Vector2f(wall.x * WALL_SIZE, wall.y * WALL_SIZE));
		walls.push_back(r);
	}*/
}

void EditorState::HandleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{

		if (event.type == sf::Event::Closed) {
			this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				lastMousePosition = sf::Mouse::getPosition();
				mouseLeftClicked = true;
			}
		}
		if (event.type == sf::Event::MouseMoved) {
			if (mouseLeftClicked)
			{
				sf::Vector2i mouseDelta = (lastMousePosition - sf::Mouse::getPosition());
				gameView.move(mouseDelta.x * zoomFactor, mouseDelta.y * zoomFactor);
				lastMousePosition = sf::Mouse::getPosition();
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mouseDelta = (lastMousePosition - sf::Mouse::getPosition());
				gameView.move(mouseDelta.x * zoomFactor, mouseDelta.y * zoomFactor);
				mouseLeftClicked = false;

			}
		}
		if (event.type == sf::Event::MouseWheelScrolled) {
			if (event.mouseWheelScroll.delta > 0) zoomFactor /= 2.0f;
			else zoomFactor *= 2.0f;
			gameView.setSize(SCREEN_WIDTH * zoomFactor, SCREEN_HEIGHT * zoomFactor);

		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
			gameView.setCenter(WALL_SIZE*ARRAY_SIZE / 2.0f, WALL_SIZE*ARRAY_SIZE / 2.0f);
		}
	}
	int testZoom = 0;
	if (gameView.getCenter().y - gameView.getSize().y / 2.0f < 0) {
		gameView.setCenter(gameView.getCenter().x, gameView.getSize().y / 2.0f);
		testZoom++;
	}
	if (gameView.getCenter().y + gameView.getSize().y / 2.0f > WALL_SIZE*ARRAY_SIZE) {
		gameView.setCenter(gameView.getCenter().x, WALL_SIZE*ARRAY_SIZE - gameView.getSize().y / 2.0f);
		testZoom++;
	}

}

void EditorState::Update(float dt)
{
	
}

void EditorState::Draw(float dt)
{
	//CLEAR AND SET WINDOW//
	this->_data->window.setView(gameView);
	this->_data->window.clear();

	//draw background
	this->_data->window.draw(_background);

	//display walls
	for (sf::RectangleShape r : walls) {
		_data->window.draw(r);
	}


	this->_data->window.setView(this->_data->window.getDefaultView());

	

	this->_data->window.display();
}


EditorState::~EditorState()
{
}
