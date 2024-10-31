#ifndef CLOUDS_H
#define CLOUDS_H

#include <SFML/Graphics.hpp>

class Cloud
{
private:
	sf::Sprite spriteColud;
	float speed{ 0 };
public:
	Cloud();

	Cloud(const sf::Texture& newTexture, const sf::Vector2f& newPos);

	Cloud(const sf::Texture& newTexture, const sf::Vector2f& newPos, const sf::Vector2f& newOrg);

	bool isActive = false;

	const sf::Sprite& getSprite() const;

	void setSpeed(const float& newSpeed);

	const float& getSpeed() const;

	void setPosition(const sf::Vector2f& newVector);

	const sf::Vector2f& getPosition() const;

};


#endif CLOUDS_H
