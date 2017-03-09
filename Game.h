#pragma once
#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include "Licence.h"
#include "Splash.h"
#include "Credits.h"
#include "Controller.h"
#include "OptionScreen.h"
#include "Game.h"

class Licence;
class Splash;
class Game;
class Credits;
class Option;

enum class
	GameState
{
	none,
	licence,
	splash,
	option,
	credits
};

class Game
{
public:
	Game();
	~Game();

	void run();
	GameState m_currentGameState;
	void SetGameState(GameState gamestate);
	bool A;
	bool B;
	bool X;
	bool Y;
	int score = 0;


private:
	void processEvents();
	void update(sf::Time, Xbox360Controller &controller);

	void render();

	sf::Font m_Impact;
	sf::Text m_textMessage[4];
	sf::RenderWindow m_window;

	Xbox360Controller m_controller;

	Splash *m_splashscreen;
	Licence *m_licence;
	Credits *m_credits;
	Option *m_option;


};

#endif // !GAME_H
