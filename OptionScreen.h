#pragma once
#ifndef OPTIONS_SCREEN
#define OPTIONS_SCREEN

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Game.h"

class Game;

class Option
{
public:
	Option(Game& game, sf::Font font);
	~Option();
	void update(sf::Time time, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);
	void changeScreen();
	void changeToOption();
	int button_ID = 0;
	bool strtgame = true;//bool for game start
	bool options = false;//bool for options 
	bool quitGame = false;//bool for quit 
	bool closeGame = false;
	bool settings = false;
	bool closeWindow = false;
	sf::RectangleShape settingButton[3];//array for buttons
										/*void changeScreen();*/
										/*Gui m_gui;
										*/
private:
	/*void volumeUpMusic();
	void volumeDownMusic();
	void volumeUpFX();
	void volumeDownFX();
	void toggleMusic();
	void toggleFX();
	void lessFrames();
	void moreFrames();*/
	Game *m_game;
	sf::Text m_textMessage[6];//text
	sf::Font m_Impact;//font
	sf::Texture m_Texture[5];//background texture
	sf::Sprite m_Sprite[5];//sprite for texture
};

#endif