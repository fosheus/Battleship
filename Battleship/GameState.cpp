#include "GameState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "PerlinNoise.h"
#include <functional>

GameState::GameState(GameDataRef data) :_data(data),shape(sf::Color::Red)
{
	
}

void triangulatePolygon(ConcaveShape &shape,int i,int size)
{
	sf::Clock one;
	one.restart();
	shape.Triangulate();
	std::cout << i << "/" << size << " size = " <<shape.getPoints().size() << " time=" << one.getElapsedTime().asSeconds() << std::endl;
	
}

void GameState::Init()
{
	this->_background.setFillColor(sf::Color::Blue);
	this->_background.setSize(sf::Vector2f(256*16, 256 * 16));

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

	

	mapGenerator.generate();
	islands.clear();
	beaches.clear();
	int max_size = 0;
	int max_elem = 0;
	for (size_t i = 0; i < mapGenerator.beaches.size(); i++)
	{
		if (max_size < mapGenerator.beaches[i].size()) {
			max_size = mapGenerator.beaches[i].size();
			max_elem = i;
		}
		beaches.push_back(ConcaveShape());
		for (size_t j = 0; j < mapGenerator.beaches[i].size(); j++)
		{
			sf::Vector2f point(mapGenerator.beaches[i][j].x*16, mapGenerator.beaches[i][j].y*16);
			beaches[beaches.size() - 1].addPoint(point);
			points.push_back(point);
		}
	}

	for (size_t i = 0; i < mapGenerator.islands.size(); i++)
	{
		islands.push_back(ConcaveShape());
		ConcaveShape & current = islands[islands.size()-1];
		for (size_t j = 0; j < mapGenerator.islands[i].size(); j++)
		{
			sf::Vector2f point(mapGenerator.islands[i][j].x*16, mapGenerator.islands[i][j].y*16);
			current.addPoint(point);
			points.push_back(point);
		}
		

	}
	std::cout << points.size() << std::endl;
	std::cout << beaches.size() << std::endl;
	sf::Clock clock;
	sf::Clock one;
	for (int i = 0; i < islands.size(); i++) {
		//distance first last
		sf::Vector2f start = islands[i].getPoints()[0];
		sf::Vector2f last = islands[i].getPoints()[islands[i].getPoints().size()-1];

		//float distance = sqrt((last.x - start.x)*(last.x - start.x) - (last.y - start.y)*(last.y - start.y));
		//if (distance < 3) {
			/*threads.push_back(new sf::Thread(std::bind(triangulatePolygon, beaches[i], i, beaches.size())));
			threads[threads.size() - 1]->launch();*/
			sf::Clock one;
			one.restart();
			islands[i].Triangulate();
			std::cout << i << "/" << islands.size() << " size = " << islands[i].getPoints().size() << " time=" << one.getElapsedTime().asSeconds() << std::endl;
		//}
	}
	std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	for (int i = 0; i < threads.size(); i++) {
		threads[i]->wait();
		delete threads[i];
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

	for (size_t i = 0; i < points.size(); i++)
	{
		
	}
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(16, 16));
	r.setFillColor(sf::Color::Yellow);

	for (size_t i = 0; i < islands.size(); i++)
	{
		/*this->_data->window.draw(islands[i]);
		sf::CircleShape c;
		c.setRadius(5);
		c.setOrigin(5, 5);
		for (int j = 0; j < islands[i].getPoints().size(); j++) {
			c.setFillColor(sf::Color(255*j/ islands[i].getPoints().size(),0, 255 *  islands[i].getPoints().size()/(j+1)));
			c.setPosition(islands[i].getPoints()[j]);
			this->_data->window.draw(c);

		}*/
		for (int j = 0; j < islands[i].getPoints().size(); j++) {
			r.setPosition(islands[i].getPoints()[j]);
			this->_data->window.draw(r);

		}
		

	}
	/*for (size_t i = 0; i < islands.size(); i++)
	{
		this->_data->window.draw(islands[i]);
	}*/
	this->_data->window.draw(rect);
	this->_data->window.setView(this->_data->window.getDefaultView());

	this->_data->window.draw(velocity);
	this->_data->window.draw(position);
	this->_data->window.draw(rotation);
	this->_data->window.draw(angle);

	this->_data->window.draw(shape);
	this->_data->window.display();
}


