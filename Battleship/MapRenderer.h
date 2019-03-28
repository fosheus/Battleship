#pragma once
#include "MapGenerator.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
class MapRenderer : public sf::Drawable
{
private:
	enum TILEPOS
	{
		WATER,
		SAND,
		ISLAND
	};
public:
	MapRenderer(std::vector<std::vector<MapGenerator::CellType>> map,const sf::Texture& terrainTexture);
	~MapRenderer();

private:
	sf::VertexArray terrain;
	const sf::Texture& terrainTexture;

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

