#pragma once
#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sfeMovie\Movie.hpp>
#include <sfeMovie\StreamSelection.hpp>
#include <sfeMovie\Visibility.hpp>
#include "Licence.h"
#include "Splash.h"
#include "Credits.h"
#include "Controller.h"
#include "OptionScreen.h"
#include "CarSelectScreen.h"
#include "Upgrade.h"
#include "SoundScreen.h"
#include "DifficultyScreen.h"
#include "Game.h"
#include "Confirm.h"
#include "Playagain.h"
#include "Gameplay.h"
#include "Help.h"
#include "Map.h"
#include "LevelLoader.h"

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
class Help;
class Map;
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
	upgrade,
	credits,
	confirm,
	gameplay,
	playagain,
	Help,
	Map,
	sound,
	Difficulty
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
	void GenerateTrack();
	int score = 0;
	sf::Sound songs[3];
	sf::SoundBuffer songBuffer[3];
	sf::Sound buttonsound;
	sf::SoundBuffer buttonBuffer;
	sf::Texture ai_Txt;
	sf::Sprite ai_Sprite;

	std::string intToString(int num); // int to string
	std::string floatToString(float num); // int to string

protected:
	LevelData m_level;
	

private:
	void processEvents();
	void update(sf::Time, Xbox360Controller &controller);

	void render();

	sf::Font m_HARLOW;
	sf::Font m_Motor;
	sf::Text m_textMessage[4];
	sf::RenderWindow m_window;
	sfe::Movie m_movie;

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
	Help *m_help;
	Map *m_map;
	Sound *m_soundScreen;
	Difficulty *m_DifficultyScreen;
	Player m_player;

	sf::View view; // camera

	std::vector<sf::CircleShape> m_trackCircle;
	std::vector<sf::CircleShape> m_trackCircle1;
	std::vector<sf::CircleShape> m_trackCircle2;

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
