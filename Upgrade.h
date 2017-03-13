#pragma once
#ifndef UPGRADE
#define UPGRADE

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Game.h"

class Game;

class Upgrade
{
public:
	Upgrade(Game& game, sf::Font font, sf::Font font1);
	~Upgrade();
	void update(sf::Time time, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);
	void changeScreen();
	void backOut();
	int button_ID = 0;
	int setting_ID = 0;

private:
	Game *m_game;
	sf::Text m_textMessage[10];//text
	sf::Font m_Motor;//font
	sf::Font m_HARLOW;
	sf::Texture m_texture[8];//background texture
	sf::Sprite m_Sprite[8];//sprite for texture
};

#endif