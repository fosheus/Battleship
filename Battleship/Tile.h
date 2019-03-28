#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Animation.h"
class Tile
{
public:
	Tile(const sf::Texture& texture,sf::Vector2f position);
	virtual void update(float multiplier) ;
	virtual void render(sf::RenderTarget* target) ;
	virtual ~Tile();

protected :
	sf::Sprite sprite;
	Animation* animation;

};

