#pragma once
#include "Game.h"
#include "Controller.h"
#include "SFML/Graphics.hpp"

class Game;
 
class Difficulty
{
public:

	Difficulty(Game &game, sf::Font font, sf::Font font2);
	~Difficulty();
	void Update(sf::Time time, Xbox360Controller &controller);
	void render(sf::RenderWindow &window);
	void changeScreen();
	int button_ID = 0;
	bool Easy = false;
	bool Medium = false;
	bool Hard = false;

private:
	Game *m_game;
	sf::Font m_motor;
	sf::Font m_harlow;
	sf::Text message[4];
	sf::Texture selectorTxt;
	sf::Sprite selectorSprite;
	sf::CircleShape difficulties[3];

};