#ifndef SPRITECONTROLLER_H
#define SPRITECONTROLLER_H

#include <SFML/Graphics.hpp>
void initSprite(sf::Sprite& spriteType, const sf::Texture& texture
	, const float posX, const float posY);

void initSprite(sf::Sprite& spriteType, const sf::Texture& texture
	, const float posX, const float posY, const float orgX, const float orgY);

#endif