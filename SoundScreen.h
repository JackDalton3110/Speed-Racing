#pragma once
#ifndef SOUND_SCREEN
#define SOUND_SCREEN

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Game.h"



class Game;

class Sound
{
public:
	Sound(Game& game, sf::Font font, sf::Font font2);
	~Sound();
	void Update(sf::Time time, Xbox360Controller &controller);
	void render(sf::RenderWindow &window);

private:
	Game *m_game;
	sf::Font m_motor;
	sf::Font m_harlow;
	sf::Text message[4];
	sf::Text m_text[3];
	sf::Texture scrollBarTxt[2];
	sf::Sprite scrollBarSprite[2];
	sf::Texture selectorTxt;
	sf::Sprite selectorSprite;
	sf::RectangleShape toggleButtons[2];
	
	void changeScreen();

	int button_ID = 0;
	int soundVolume = 100;
	bool on = true;
	bool off = false;
	bool FXon = true;
	bool FXoff = false;
	bool volume = false;

	std::string intToString(int num); // int to string
};

#endif