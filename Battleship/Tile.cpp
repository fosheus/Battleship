#include "Tile.h"



Tile::Tile(const sf::Texture & texture, sf::Vector2f position)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Tile::update(float multiplier)
{
	if (animation) {
		animation->update(0, multiplier);
		sprite.setTextureRect(animation->uvRect);
	}
}

void Tile::render(sf::RenderTarget * target)
{
	if (target) {
		target->draw(sprite);
	}
}

Tile::~Tile()
{
	delete animation;
}
