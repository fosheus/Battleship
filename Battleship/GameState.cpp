#include "GameState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "PerlinNoise.h"


GameState::GameState(GameDataRef data) :_data(data),shape(sf::Color::Red)
{
	
}

void GameState::Init()
{
	this->_background.setTexture(this->_data->assets.GetImage(GAME_STATE_BACKGROUND_FILEPATH));
	this->_background.setPosition(this->_data->window.getSize().x / 2 - this->_background.getGlobalBounds().width / 2, this->_data->window.getSize().y / 2 - this->_background.getGlobalBounds().height / 2);
	
	this->velocity.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));
	this->rotation.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));
	this->position.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));
	this->angle.setFont(this->_data->assets.GetFont("fonts/basic_font.ttf"));

	

	this->velocity.setScale(sf::Vector2f(0.5,0.5));
	this->position.setScale(sf::Vector2f(0.5, 0.5));
	this->rotation.setScale(sf::Vector2f(0.5, 0.5));
	this->angle.setScale(sf::Vector2f(0.5, 0.5));

	this->velocity.setPosition(sf::Vector2f(0,0));
	this->position.setPosition(sf::Vector2f(0, 20));
	this->rotation.setPosition(sf::Vector2f(0, 40));
	this->angle.setPosition(sf::Vector2f(0, 60));

	ship.setPosition(sf::Vector2f(100, 100));
	ship.setAcceleration(1.0f);

	gameView.setCenter(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	zoomFactor = 1.0f;
	this->mouseLeftClicked = false;

	/*shape.addPoint(sf::Vector2f(15, 11));
	shape.addPoint(sf::Vector2f(30, 15));
	shape.addPoint(sf::Vector2f(35, 28));
	shape.addPoint(sf::Vector2f(27, 32));
	shape.addPoint(sf::Vector2f(30, 45));
	shape.addPoint(sf::Vector2f(20, 50));
	shape.addPoint(sf::Vector2f(15, 38));
	shape.addPoint(sf::Vector2f(2, 31));
	shape.addPoint(sf::Vector2f(15, 25));
	shape.addPoint(sf::Vector2f(15, 19));
	shape.Triangulate();*/

	PerlinNoise::SetupPerlinNoise(&fNoiseSeed2D, &fPerlinNoise2D, arraySize, arraySize);

	PerlinNoise::PerlinNoise2D(arraySize, arraySize, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);


	vertices.resize(arraySize *arraySize* 4);
	vertices.setPrimitiveType(sf::Quads);
	

	for (int x = 0; x < arraySize; x++)
	{
		for (int y = 0; y < arraySize; y++)
		{
			sf::Vertex* vertex = &vertices[(x + y * arraySize) * 4];
			int tileNumber = (int)(fPerlinNoise2D[y * arraySize + x] * 12.0f);

			vertex[0].position = sf::Vector2f(x*16, y*16);
			vertex[1].position = sf::Vector2f((x+1)*16, y*16);
			vertex[2].position = sf::Vector2f((x+1)*16, (y+1)*16);
			vertex[3].position = sf::Vector2f(x*16, (y+1)*16);

			switch (tileNumber)
			{
			case 9:
				vertex[0].color = sf::Color::Yellow;
				vertex[1].color = sf::Color::Yellow;
				vertex[2].color = sf::Color::Yellow;
				vertex[3].color = sf::Color::Yellow;
				break;
			case 10:
			case 11:
			case 12:
				vertex[0].color = sf::Color::Green;
				vertex[1].color = sf::Color::Green;
				vertex[2].color = sf::Color::Green;
				vertex[3].color = sf::Color::Green;
				break;
			default:
				vertex[0].color = sf::Color::Blue;
				vertex[1].color = sf::Color::Blue;
				vertex[2].color = sf::Color::Blue;
				vertex[3].color = sf::Color::Blue;
				break;
			}
		}
	}


	

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
			if (event.mouseWheelScroll.delta>0) zoomFactor/=2.0f;
			else zoomFactor *= 2.0f;
			gameView.setSize(SCREEN_WIDTH * zoomFactor, SCREEN_HEIGHT * zoomFactor);

		}
	}
}

void GameState::Update(float dt)
{

	ship.update(dt);

	this->velocity.setString("velocity:"+std::to_string(ship.getCurrentVelocity())+" => "+ std::to_string(ship.getTargetVelocity()));
	this->position.setString("position:"+std::to_string(ship.getPosition().x)+";"+ std::to_string(ship.getPosition().y));
	this->rotation.setString("rotation:" + std::to_string(ship.getCurrentRotation()) + " => " + std::to_string(ship.getTargetRotation()));
	this->angle.setString("angle:" + std::to_string(ship.getAngle()));

	/*shape.setPosition(sf::Vector2f(shape.getPosition().x+2, shape.getPosition().y+1));
	shape.Triangulate();
	*/
}

void GameState::Draw(float dt)
{
	//CLEAR AND SET WINDOW//
	this->_data->window.setView(gameView);
	this->_data->window.clear();
	
	this->_data->window.draw(_background);
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(201,31));
	rect.setOrigin(sf::Vector2f(100, 15));
	rect.setPosition(ship.getPosition());
	rect.setFillColor(sf::Color::Green);
	rect.setRotation(ship.getAngle());	
	this->_data->window.draw(vertices);
	this->_data->window.draw(rect);
	this->_data->window.setView(this->_data->window.getDefaultView());

	this->_data->window.draw(velocity);
	this->_data->window.draw(position);
	this->_data->window.draw(rotation);
	this->_data->window.draw(angle);

	this->_data->window.draw(shape);
	this->_data->window.display();
}

