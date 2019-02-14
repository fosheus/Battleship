#include "GameState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "PerlinNoise.h"
#include <functional>

GameState::GameState(GameDataRef data) :_data(data)
{

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
	const std::vector<sf::Vector2i>& mapWalls  = mapGenerator.generate();
	sf::RectangleShape r;
	r.setFillColor(sf::Color::Yellow);
	r.setSize(sf::Vector2f(WALL_SIZE, WALL_SIZE));
	wallsTexture.create(WALL_SIZE*ARRAY_SIZE, WALL_SIZE*ARRAY_SIZE);
	for (sf::Vector2i wall : mapWalls) {
		r.setPosition(sf::Vector2f(wall.x * WALL_SIZE, wall.y * WALL_SIZE));
		walls.push_back(r);
		wallsTexture.draw(r);
	}
	wallsTexture.display();
}

int GameState::pnpoly(std::vector<sf::Vector2f>& points, sf::Vector2f testPoint)
{

	int i, j, c = 0;
	for (i = 0, j = points.size() - 1; i < points.size(); j = i++) {
		if (((points[i].y > testPoint.y) != (points[j].y > testPoint.y)) &&
			(testPoint.x < (points[j].x - points[i].x) * (testPoint.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
			c = !c;
	}
	return c;

}

bool GameState::rectanglesCollide(std::vector<sf::Vector2f>& rect1, std::vector<sf::Vector2f>& rect2) {
	for (int i = 0; i < rect1.size(); i++) {
		if (pnpoly(rect2, rect1[i])!=0) {
			return true;
		}
	}
	return false;
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

	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		gameView.setCenter(ship.getPosition());
	}

	int testZoom = 0;
	if (gameView.getCenter().y - gameView.getSize().y / 2.0f< 0) {
		gameView.setCenter(gameView.getCenter().x, gameView.getSize().y / 2.0f);
		testZoom++;
	}
	if (gameView.getCenter().y + gameView.getSize().y / 2.0f > WALL_SIZE*ARRAY_SIZE) {
		gameView.setCenter(gameView.getCenter().x, WALL_SIZE*ARRAY_SIZE- gameView.getSize().y / 2.0f);
		testZoom++;
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

	bool shipCollidesWithWall = false;
	sf::Clock clocktest;
	sf::FloatRect rect = ship.getGlobalBounds();
	std::vector<sf::Vector2f> shapePoints = ship.getPoints();

	for (sf::RectangleShape& r : walls) {
		if (r.getGlobalBounds().intersects(rect)) {
			std::vector<sf::Vector2f> rectPoints;
			rectPoints.push_back(r.getPoint(0)+r.getPosition());
			rectPoints.push_back(r.getPoint(1) + r.getPosition());
			rectPoints.push_back(r.getPoint(2) + r.getPosition());
			rectPoints.push_back(r.getPoint(3) + r.getPosition());
			if (rectanglesCollide(rectPoints, shapePoints)) {
				shipCollidesWithWall = true;
			}
		}
	}
	if (shipCollidesWithWall) {
		ship.decelerate(5, 1, dt);
	}
	
	ship.update(dt);


	this->velocity.setString("velocity:" + std::to_string(ship.getCurrentVelocity()) + " => " + std::to_string(ship.getTargetVelocity()));
	this->position.setString("position:" + std::to_string(ship.getPosition().x) + ";" + std::to_string(ship.getPosition().y));
	this->rotation.setString("rotation:" + std::to_string(ship.getCurrentRotation()) + " => " + std::to_string(ship.getTargetRotation()));
	this->angle.setString("angle:" + std::to_string(ship.getAngle()));

}

void GameState::Draw(float dt)
{
	//CLEAR AND SET WINDOW//
	this->_data->window.setView(gameView);
	this->_data->window.clear();

	//draw background
	this->_data->window.draw(_background);

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
	sf::CircleShape c;
	c.setRadius(10);
	c.setOrigin(5,5);
	c.setFillColor(sf::Color::Magenta);
	for (sf::Vector2f p : shapePoints) {
		c.setPosition(p);
		_data->window.draw(c);
	}

	this->_data->window.setView(this->_data->window.getDefaultView());

	//draw HUD
	this->_data->window.draw(velocity);
	this->_data->window.draw(position);
	this->_data->window.draw(rotation);
	this->_data->window.draw(angle);

	this->_data->window.display();
}




