#include "Clouds.h"
#include <SFML/Graphics.hpp>


Cloud::Cloud()
{

}
Cloud::Cloud(const sf::Texture& newTexture, const sf::Vector2f& newPos)
{
	spriteColud.setTexture(newTexture);
	spriteColud.setPosition(newPos);
}
Cloud::Cloud(const sf::Texture& newTexture, const sf::Vector2f& newPos, const sf::Vector2f& newOrg)
{
	spriteColud.setTexture(newTexture);
	spriteColud.setPosition(newPos);
	spriteColud.setOrigin(newOrg);
}


const sf::Sprite& Cloud::getSprite() const
{
	return spriteColud;
}
void Cloud::setSpeed(const float& newSpeed)
{
	speed = newSpeed;
}

const float& Cloud::getSpeed() const
{
	return speed;
}
void Cloud::setPosition(const sf::Vector2f& newVector)
{
	spriteColud.setPosition(newVector);
}
const sf::Vector2f& Cloud::getPosition() const
{
	return spriteColud.getPosition();
}
