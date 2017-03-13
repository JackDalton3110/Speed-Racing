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
	void changeScreen();
	void Update(sf::Time time, Xbox360Controller &controller);
	void render(sf::RenderWindow &window);
	int button_ID = 0;
	int soundVolume=10;
	bool Music =true;
	bool FX = false;
	bool volume = false;

private:
	Game *m_game;
	sf::Font m_motor;
	sf::Font m_harlow;
	sf::Text message[4];
	sf::Texture scrollBarTxt[2];
	sf::Sprite scrollBarSprite[2];
	sf::Texture selectorTxt;
	sf::Sprite selectorSprite;
	sf::RectangleShape toggleButtons[2];
	
};

#endif