#include "MapRenderer.h"




MapRenderer::MapRenderer(std::vector<std::vector<MapGenerator::CellType>> map,const sf::Texture& terrainTexture) : terrainTexture(terrainTexture)
{
	terrain.resize(ARRAY_SIZE*ARRAY_SIZE * 4);
	terrain.setPrimitiveType(sf::PrimitiveType::Quads);
	
	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			sf::Vertex* tile = &terrain[(i + j * ARRAY_SIZE) * 4];
			int x = map[i][j];
			int y = 0;
			tile[0].position = sf::Vector2f(i*WALL_SIZE, j*WALL_SIZE);
			tile[1].position = sf::Vector2f(i*WALL_SIZE, (j + 1)*WALL_SIZE);
			tile[2].position = sf::Vector2f((i + 1)*WALL_SIZE, (j + 1)*WALL_SIZE);
			tile[3].position = sf::Vector2f((i + 1)*WALL_SIZE, j*WALL_SIZE);
			
			tile[0].texCoords = sf::Vector2f(x*WALL_SIZE, y*WALL_SIZE);
			tile[1].texCoords = sf::Vector2f(x*WALL_SIZE, (y + 1)*WALL_SIZE);
			tile[2].texCoords = sf::Vector2f((x + 1)*WALL_SIZE, (y + 1)*WALL_SIZE);
			tile[3].texCoords = sf::Vector2f((x + 1)*WALL_SIZE, y*WALL_SIZE);

			
			}
		}
	

}


MapRenderer::~MapRenderer()
{
}

void MapRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.texture = &terrainTexture;
	target.draw(terrain,states);
}
