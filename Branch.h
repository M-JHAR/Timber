#ifndef BRANCH_H
#define BRANCH_H

#include <SFML/Graphics.hpp>




namespace bo
{
	

	class Branch
	{
	private:
		sf::Sprite spriteColud;
		float speed{ 0 };
	public:
		Branch();

		Branch(const sf::Texture& newTexture, const sf::Vector2f& newPos);

		Branch(const sf::Texture& newTexture, const sf::Vector2f& newPos, const sf::Vector2f& newOrg);


		const sf::Sprite& getSprite() const;

		void setSpeed(const float& newSpeed);

		const float& getSpeed() const;

		void setPosition(const sf::Vector2f& newVector);

		const sf::Vector2f& getPosition() const;


	};
	
	
}

#endif BRANCH_H