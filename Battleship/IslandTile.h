#pragma once
#include "Tile.h"
class IslandTile :
	public Tile
{
public:
	IslandTile(const sf::Texture & texture,sf::Vector2f position);
	~IslandTile();
};

