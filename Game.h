#pragma once
#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Licence.h"
#include "Splash.h"
#include "Credits.h"
#include "Controller.h"
#include "OptionScreen.h"
#include "CarSelectScreen.h"
#include "SoundScreen.h"
#include "DifficultyScreen.h"
#include "Game.h"

class Licence;
class Splash;
class CarSelect;
class Game;
class Credits;
class Option;
class Sound;
class Difficulty;

enum class
	GameState
{
	none,
	licence,
	splash,
	carSelect,
	option,
	sound,
	Difficulty,
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
	sf::Sound songs[3];
	sf::SoundBuffer songBuffer[3];
	sf::Sound buttonsound;
	sf::SoundBuffer buttonBuffer;


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
	Sound *m_soundScreen;
	Difficulty *m_DifficultyScreen;

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
