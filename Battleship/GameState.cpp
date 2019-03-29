#include "GameState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "PerlinNoise.h"
#include <functional>
#include "Collider.h"

GameState::GameState(GameDataRef data) :_data(data)
{

}

GameState::~GameState()
{
	for (size_t i = 0; i < terrain.size(); i++)
	{
		delete terrain[i];
	}
	delete mapRenderer;
}


void GameState::initGUI()
{
	this->_background.setFillColor(sf::Color::Blue);
	this->_background.setSize(sf::Vector2f(ARRAY_SIZE * WALL_SIZE, ARRAY_SIZE * WALL_SIZE));

	this->velocity.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));
	this->rotation.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));
	this->position.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));
	this->angle.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));



	this->velocity.setScale(sf::Vector2f(0.5, 0.5));
	this->position.setScale(sf::Vector2f(0.5, 0.5));
	this->rotation.setScale(sf::Vector2f(0.5, 0.5));
	this->angle.setScale(sf::Vector2f(0.5, 0.5));

	this->velocity.setPosition(sf::Vector2f(0, 0));
	this->position.setPosition(sf::Vector2f(0, 20));
	this->rotation.setPosition(sf::Vector2f(0, 40));
	this->angle.setPosition(sf::Vector2f(0, 60));


	gameView.setCenter(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	zoomFactor = 1.0f;

}


void GameState::initEntities()
{
	ship.setPosition(sf::Vector2f(100, 100));
	ship.setAcceleration(1.0f);
	ship.setMaxRotation(20.0f);
	ship.setMaxVelocity(10.0f);
}

void GameState::initWalls()
{
	std::vector<std::vector<MapGenerator::CellType>> cellType = mapGenerator.generate();

	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			switch (cellType[i][j])
			{

			case MapGenerator::ISLAND:
				terrain.push_back(new IslandObstacle(sf::Vector2f(i*WALL_SIZE, j*WALL_SIZE), sf::Vector2f(WALL_SIZE, WALL_SIZE)));
				break;

			case MapGenerator::BEACH:
				terrain.push_back(new SandObstacle(sf::Vector2f(i*WALL_SIZE, j*WALL_SIZE), sf::Vector2f(WALL_SIZE, WALL_SIZE)));
				break;

			default:
				break;
			}
		}
	}
	mapRenderer = new MapRenderer(cellType, _data->assets.GetImage(TERRAIN_SPRTIESHEET));

}


void GameState::manageInputShipMouvement(sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Q) {
			ship.addRotation(-1);
		}
		if (event.key.code == sf::Keyboard::D) {
			ship.addRotation(1);
		}
		if (event.key.code == sf::Keyboard::Z) {
			ship.addVelocity(1);
		}
		if (event.key.code == sf::Keyboard::S) {
			ship.addVelocity(-1);
		}
	}
}


void GameState::manageInputGameView(sf::Event & event)
{
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
		std::cout << gameView.getSize().x << " " << gameView.getSize().y << std::endl;
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		gameView.setCenter(ship.getPosition());
	}

	if (gameView.getCenter().y - gameView.getSize().y / 2.0f < 0) {
		gameView.setCenter(gameView.getCenter().x, gameView.getSize().y / 2.0f);
	}
	if (gameView.getCenter().y + gameView.getSize().y / 2.0f > WALL_SIZE*ARRAY_SIZE) {
		gameView.setCenter(gameView.getCenter().x, WALL_SIZE*ARRAY_SIZE - gameView.getSize().y / 2.0f);
	}



}


void GameState::Init()
{

	this->initGUI();

	this->initEntities();

	this->initWalls();

	this->mouseLeftClicked = false;

}


void GameState::HandleInput()
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


		manageInputGameView(event);
		manageInputShipMouvement(event);
	}
}

void GameState::Update(float dt)
{
	ship.update(dt);
	checkTerrainCollision(dt);
	checkEntitiesCollision(dt);

	this->velocity.setString("velocity:" + std::to_string(ship.getCurrentVelocity()) + " => " + std::to_string(ship.getTargetVelocity()));
	this->position.setString("position:" + std::to_string(ship.getPosition().x) + ";" + std::to_string(ship.getPosition().y));
	this->rotation.setString("rotation:" + std::to_string(ship.getCurrentRotation()) + " => " + std::to_string(ship.getTargetRotation()));
	this->angle.setString("angle:" + std::to_string(ship.getAngle()));

}

void GameState::checkTerrainCollision(float dt)
{

	bool shipCollidesWithBeach = false;
	bool shipCollidesWithIsland = false;
	sf::FloatRect rect = ship.getGlobalBounds();
	std::vector<sf::Vector2f> shapePoints = ship.getPoints();

	for (ICollidable* obstacle : terrain) {
		if (obstacle != NULL) {
			sf::FloatRect obstacleGlobalBounds = obstacle->getGlobalBounds();
			if (obstacleGlobalBounds.intersects(rect)) {
				std::vector<sf::Vector2f> obstaclePoints = obstacle->getPoints();
				CollisionResponse collisionResponse = Collider::checkTerrainCollision(ship, *obstacle);
				if (collisionResponse.intersect) {
					ship.resolveCollision(*obstacle, collisionResponse);
					this->collisionResponse = collisionResponse;
				}
			}
		}
	}

}

void GameState::checkEntitiesCollision(float dt)
{
}


void GameState::Draw(float dt)
{
	//CLEAR AND SET WINDOW//
	this->_data->window.setView(gameView);
	this->_data->window.clear();

	_data->window.draw(*mapRenderer);

	//display walls
	sf::Sprite wallsSprite;
	wallsSprite.setTexture(wallsTexture.getTexture());
	_data->window.draw(wallsSprite);

	//draw ship
	ship.render(&_data->window);

	//draw ship bounding box
	sf::FloatRect floatrect = ship.getGlobalBounds();
	sf::RectangleShape r;
	r.setPosition(floatrect.left, floatrect.top);
	r.setSize(sf::Vector2f(floatrect.width, floatrect.height));
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineColor(sf::Color::Red);
	r.setOutlineThickness(3);
	this->_data->window.draw(r);

	//draw ship points
	std::vector<sf::Vector2f> shapePoints = ship.getPoints();
	sf::Vertex lines[4][2];
	lines[0][0].position = shapePoints[0];
	lines[0][1].position = shapePoints[1];
	lines[1][0].position = shapePoints[2];
	lines[1][1].position = shapePoints[3];
	lines[2][0].position = shapePoints[1];
	lines[2][1].position = shapePoints[2];
	lines[3][0].position = shapePoints[3];
	lines[3][1].position = shapePoints[0];

	_data->window.draw(lines[0], 2, sf::PrimitiveType::Lines);
	_data->window.draw(lines[1], 2, sf::PrimitiveType::Lines);
	_data->window.draw(lines[2], 2, sf::PrimitiveType::Lines);
	_data->window.draw(lines[3], 2, sf::PrimitiveType::Lines);

	
	this->_data->window.setView(this->_data->window.getDefaultView());

	//draw HUD
	this->_data->window.draw(velocity);
	this->_data->window.draw(position);
	this->_data->window.draw(rotation);
	this->_data->window.draw(angle);

	this->_data->window.display();
}




