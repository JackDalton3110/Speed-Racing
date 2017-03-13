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
	void reset();
	int button_ID = 0;
	int setting_ID = 0;
	bool startgame = true;//bool for game start
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
	
	Game *m_game;

	sf::Text m_textMessage[10];//text
	sf::Font m_Motor;//font
	sf::Font m_HARLOW;
	sf::Texture m_Texture[8];//background texture
	sf::Sprite m_Sprite[8];//sprite for texture

	bool m_button_released; // chenk player release A button
	bool m_reset_check; // 

};

#endif