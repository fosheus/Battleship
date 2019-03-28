#include "SandTile.h"



SandTile::SandTile(const sf::Texture& texture, sf::Vector2f position): Tile(texture,position)
{
	animation = new Animation(&texture, sf::Vector2u(1, 1), 1);
}


SandTile::~SandTile()
{
}


