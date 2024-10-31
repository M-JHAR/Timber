#include "Branch.h"
#include <SFML/Graphics.hpp>


namespace bo
{


	bo::Branch::Branch()
	{

	}
	bo::Branch::Branch(const sf::Texture& newTexture, const sf::Vector2f& newPos)
	{
		spriteColud.setTexture(newTexture);
		spriteColud.setPosition(newPos);
	}
	bo::Branch::Branch(const sf::Texture& newTexture, const sf::Vector2f& newPos, const sf::Vector2f& newOrg)
	{
		spriteColud.setTexture(newTexture);
		spriteColud.setPosition(newPos);
		spriteColud.setOrigin(newOrg);
	}

	const sf::Sprite& bo::Branch::getSprite() const
	{
		return spriteColud;
	}
	void bo::Branch::setSpeed(const float& newSpeed)
	{
		speed = newSpeed;
	}

	const float& bo::Branch::getSpeed() const
	{
		return speed;
	}
	void bo::Branch::setPosition(const sf::Vector2f& newVector)
	{
		spriteColud.setPosition(newVector);
	}
	const sf::Vector2f& bo::Branch::getPosition() const
	{
		return spriteColud.getPosition();
	}

}
