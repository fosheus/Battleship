#pragma once
#include "Tile.h"
class WaterTile :
	public Tile
{
public:
	WaterTile(const sf::Texture& texture, sf::Vector2f position);
	~WaterTile();

};

