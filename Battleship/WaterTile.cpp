#include "WaterTile.h"





WaterTile::WaterTile(const sf::Texture & texture, sf::Vector2f position) : Tile(texture,position)
{
	animation = new Animation(&texture, sf::Vector2u(8, 1), 0.5);

}

WaterTile::~WaterTile()
{
}

