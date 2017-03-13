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
#include "CarSelectScreen.h"
#include "Upgrade.h"
#include "Game.h"
#include "Confirm.h"
#include "Playagain.h"
#include "Gameplay.h"

class Licence;
class Splash;
class Gameplay;
class CarSelect;
class Game;
class Credits;
class Option;
class Upgrade;
class Confirm;
class Playagain;


enum class
	GameState
{
	none,
	licence,
	splash,
	carSelect,
	option,
	upgrade,
	credits,
	confirm,
	gameplay,
	playagain

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

	sf::Font m_HARLOW;
	sf::Font m_Motor;
	sf::Text m_textMessage[4];
	sf::RenderWindow m_window;

	Xbox360Controller m_controller;

	Splash *m_splashscreen;
	CarSelect *m_carSelect;
	Licence *m_licence;
	Credits *m_credits;
	Option *m_option;
	Upgrade *m_upgrade;
	Confirm *m_confirm;
	Playagain *m_again;
	Gameplay *m_gameplay;

	sf::Texture m_Texture1;
	sf::Texture m_Texture2;
	sf::Texture m_Texture3;
	sf::Texture m_Texture4;
	sf::Texture m_Texture5;
	sf::Sprite m_Sprite1;
	sf::Sprite m_Sprite3;
	sf::Sprite m_Sprite2;
	sf::Sprite m_Sprite4;
	sf::Sprite m_Sprite5;


};

#endif // !GAME_H
