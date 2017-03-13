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
	Option(Game& game, sf::Font font, sf::Font font1);
	~Option();
	void update(sf::Time time, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);
	void changeScreen();
	void changeToOption();
	int button_ID = 0;
	int setting_ID = 0;
	bool strtgame = true;//bool for game start
	bool options = false;//bool for options 
	bool quitGame = false;//bool for quit 
	bool upgrade = false;
	bool closeGame = false;
	bool settings = false;
	bool closeWindow = false;
	sf::RectangleShape settingButton[9];//array for buttons
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
	sf::Text m_textMessage[10];//text
	sf::Font m_Motor;//font
	sf::Font m_HARLOW;
	sf::Texture m_Texture[8];//background texture
	sf::Sprite m_Sprite[8];//sprite for texture
};

#endif