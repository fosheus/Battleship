#include "IslandTile.h"


IslandTile::IslandTile(const sf::Texture & texture, sf::Vector2f position) : Tile(texture,position)
{
	animation = new Animation(&texture, sf::Vector2u(1, 1), 1);

}

IslandTile::~IslandTile()
{
}
