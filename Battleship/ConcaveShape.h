#pragma once
//---------------------------------------------------------------------------//
#include <vector>
//-----------------------------------//
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class ConcaveShape : public sf::Drawable, public sf::Transformable {
private:
	std::vector<sf::VertexArray> triangles;
	std::vector<sf::Vector2f> points;
	sf::Color color;
	const sf::Texture* texture;
	float Area() const;
	bool PointOnLine(sf::Vector2f pt, sf::Vector2f v1, sf::Vector2f v2) const;
	bool PointInTriangle(sf::Vector2f p, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) const;
	void CreateTriangle(unsigned int a, unsigned int b, unsigned int c);
	void TriangulateInner(unsigned int n, std::vector<unsigned int>& p);
public:
	explicit ConcaveShape(sf::Color c = sf::Color::Black);
	explicit ConcaveShape(const sf::Texture& t, sf::Color c = sf::Color::Black);
	~ConcaveShape();
	void addPoint(sf::Vector2f point);
	void Triangulate();
	void setColor(sf::Color c);
	void setTexture(const sf::Texture& t);
	std::vector<sf::Vector2f>& getPoints() { return points; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = texture;
		for (unsigned int i = 0; i < triangles.size(); ++i) {
			target.draw(triangles.at(i), states);
		}
	}
};
//---------------------------------------------------------------------------//
