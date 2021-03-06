#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Vector2f.h"

/**
* Description: This class is used for creating a piece of environment (worker areas, spawn areas) etc..
*/
class Environment
{
public:
	Environment(float x, float y, std::string _tag);
	~Environment();

	void draw(sf::RenderWindow& win);
	void setTexture(ResourceManager& resources, std::string textureName);

	//Setters
	void setRotation(float angle);
	void setScale(float x, float y);

	std::string tag;
	Vector2f m_position;
	sf::Sprite m_sprite;
	float angle;

	//Getters
	sf::FloatRect collider() { return m_collider; }
private:
	sf::FloatRect m_collider;
};

