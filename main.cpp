#include "SpriteController.h"
#include "Clouds.h"
//#include "Branch.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <sstream>




enum class side { s_LEFT, s_RIGHT, s_NONE };
const int NUM_BRANCHES = 6;

side branchPositions[NUM_BRANCHES];
sf::Sprite branches[NUM_BRANCHES];

void updateBranches(int seed);


int main()
{
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Timber", sf::Style::Fullscreen);

	//Background Texture & Sprite
	sf::Texture textureBackgorund;
	textureBackgorund.loadFromFile("graphics/background.png");

	sf::Sprite spriteBackground;
	initSprite(spriteBackground, textureBackgorund, 0, 0);

	//Tree Texture & Sprite
	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	sf::Sprite spriteTree;
	initSprite(spriteTree, textureTree, 810, 0);


	//Bee Texture & Sprite
	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");

	sf::Sprite spriteBee;
	initSprite(spriteBee, textureBee, 0, 810);

	bool beeActive = false;
	float beeSpeed{};



	//Clouds Texture & Sprite
	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	const int NUM_CLOUDS = 3;
	Cloud clouds[NUM_CLOUDS];
	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		Cloud c(textureCloud, sf::Vector2(0.f, i * 150.f));
		c.setSpeed(0.f);
		c.isActive = false;

		clouds[i] = c;
	}



	//deltaTime And Timmer
	sf::Clock clock;

	sf::RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;

	timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition((1920 / 2.f) - timeBarStartWidth / 2, 980.f);

	sf::Time gameTimeTotal{};
	float timeRemaning = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaning;





	bool paused = true;
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");


	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	messageText.setPosition(1920 / 2.f, 1080 / 2.f);

	scoreText.setPosition(20, 20);



	//**** BRANCH TEXTURE LOADING *****//
	sf::Texture	textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		sf::Sprite s;
		s.setTexture(textureBranch);

		branches[i] = s;
		initSprite(branches[i], textureBranch, -2000, -2000, 220, 20);
		
	}
	//**** BRANCH TEXTURE LOADING *****//




	//Player Sprite & Texture
	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	sf::Sprite spritePlayer;
	initSprite(spritePlayer, texturePlayer, 580.f, 720.f);

	side playerSide = side::s_LEFT;

	//Gravestone Sprite & Texture
	sf::Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	sf::Sprite spriteRIP;
	initSprite(spriteRIP, textureRIP, 600.f, 800.f);

	//Axe Sprite & Texture
	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	sf::Sprite spriteAxe;
	initSprite(spriteAxe, textureAxe, 700.f, 830.f);

	//Logg Implementation
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	sf::Sprite spriteLog;
	initSprite(spriteLog, textureLog, 810.f, 720.f);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	// *** Load all the sounds ***
	sf::SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	sf::Sound chop;
	chop.setBuffer(chopBuffer);

	sf::SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	sf::Sound death;
	death.setBuffer(deathBuffer);

	//Out of time - oot
	sf::SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	sf::Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);



	bool isScoreChanged = false;


	//********************************************************************************//


	sf::Event event;
	while (window.isOpen())
	{
		//*// respond to user input
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && !paused)
			{
				acceptInput = true;
				spriteAxe.setPosition(2000.f, spriteAxe.getPosition().y);
			}
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
		{
			paused = false;
			score = 0;

			timeRemaning = 6;

			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::s_NONE;
			}

			spriteRIP.setPosition(675.f, 2000.f);
			spritePlayer.setPosition(580.f, 720.f);
			acceptInput = true;
		}

		if (acceptInput)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			{
				playerSide = side::s_RIGHT;

				score++;
				isScoreChanged = true;

				timeRemaning += (2.f / score) + .15f;

				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200.f, 720.f);


				updateBranches(score);

				spriteLog.setPosition(810.f, 720.f);

				logSpeedX = -5000.f;
				logActive = true;

				acceptInput = false;

				//Play chop sound
				chop.play();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				playerSide = side::s_LEFT;

				score++;
				isScoreChanged = true;

				timeRemaning += (2.f / score) + .15f;

				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580.f, 720.f);


				updateBranches(score);

				spriteLog.setPosition(810.f, 720.f);
				logSpeedX = 5000.f;
				logActive = true;

				acceptInput = false;

				//Play chop sound
				chop.play();
			}
		}
		//*//

		//* update all the gameobjects
		if (!paused)
		{
			sf::Time dt = clock.restart();
			timeRemaning -= dt.asSeconds();
			timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaning, timeBarHeight));

			if (timeRemaning <= 0)
			{
				paused = true;

				messageText.setString("Out of time!");
				textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.width / 2.f + textRect.left, textRect.height / 2.f + textRect.top);
				messageText.setPosition(1920.f / 2, 1080 / 2.f);
				messageText.setFillColor(sf::Color::Red);

				//play out of time Sound
				outOfTime.play();
			}
			if (!beeActive)
			{
				srand((unsigned)time(0));
				beeSpeed = (rand() % 200) + 200.f;

				srand((unsigned)time(0) * 10);
				float height = (rand() % 500) + 500.f;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}

			//**********UPDATE CLOUD MOVEMENT***********//
			for (int i = 0; i < NUM_CLOUDS; i++)
			{
				if (!clouds[i].isActive)
				{
					srand((unsigned)time(0) * (i + 1) * 5);
					clouds[i].setSpeed((float)(rand() % 200));

					srand((unsigned)time(0) * (i + 5) * 10);
					float height = (rand() % 150) + 0.f;
					clouds[i].setPosition(sf::Vector2f(-200.f, height));
					clouds[i].isActive = true;
				}
				else
				{
					Cloud& c = clouds[i];
					c.setPosition(sf::Vector2f(c.getPosition().x + (c.getSpeed() * dt.asSeconds()), c.getPosition().y));

					if (c.getPosition().x > 1920.f)
					{
						clouds[i].isActive = false;
					}
				}

			}
			//**********UPDATE CLOUD MOVEMENT***********//

			if (isScoreChanged)
			{
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());
				isScoreChanged = false;
			}


			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150.f;

				if (branchPositions[i] == side::s_LEFT)
				{
					branches[i].setPosition(610, height);

					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::s_RIGHT)
				{
					branches[i].setPosition(1330, height);

					branches[i].setRotation(0);
				}
				else
				{
					branches[i].setPosition(3000, height);
				}
			}

			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds())
					, spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					logActive = false;
					spriteLog.setPosition(810.f, 720.f);
				}

				if (branchPositions[5] == playerSide)
				{
					//death
					paused = true;
					acceptInput = false;

					spriteRIP.setPosition(525.f, 760.f);

					spritePlayer.setPosition(2000.f, 660.f);

					messageText.setString("SQUISHED!!");
					textRect = messageText.getLocalBounds();
					messageText.setOrigin(textRect.width / 2.f + textRect.left, textRect.height / 2.f + textRect.top);
					messageText.setPosition(1920.f / 2, 1080 / 2.f);

					messageText.setFillColor(sf::Color::Red);

					//play sound of death
					death.play();
				}
			}

			//END IF PAUSED
		}


		//* draw all the gameobjects

		window.clear();

		window.draw(spriteBackground);

		for (int i = 0; i < NUM_CLOUDS; i++)
		{
			window.draw(clouds[i].getSprite());
		}

		for (int i = 0; i < NUM_BRANCHES; i++)
			window.draw(branches[i]);

		window.draw(spriteTree);

		window.draw(spritePlayer);

		window.draw(spriteAxe);

		window.draw(spriteLog);

		window.draw(spriteRIP);

		window.draw(spriteBee);

		window.draw(scoreText);

		window.draw(timeBar);

		if (paused)
		{
			window.draw(messageText);
		}


		window.display();
	}


}





void initSprite(sf::Sprite& spriteType, const sf::Texture& texture
	, const float posX, const float posY)
{
	spriteType.setTexture(texture);
	spriteType.setPosition(posX, posY);
}
void initSprite(sf::Sprite& spriteType, const sf::Texture& texture
	, const float posX, const float posY, const float orgX, const float orgY)
{
	spriteType.setTexture(texture);
	spriteType.setPosition(posX, posY);
	spriteType.setOrigin(orgX, orgY);
}








void updateBranches(int seed)
{
	for (int j = 6 - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}
	srand((unsigned)time(0) + seed);
	int r = (rand() % 5); // 0 to 4 included

	switch (r)
	{
	case 0:
		branchPositions[0] = side::s_LEFT;
		break;
	case 1:
		branchPositions[0] = side::s_RIGHT;
		break;

	default:
		branchPositions[0] = side::s_NONE;
		break;
	}
}
