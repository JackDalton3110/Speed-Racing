#pragma once
#ifndef PLAYAGAIN
#define PLAYAGAIN

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Controller.h"

class Game;

class Playagain
{
public:
	Playagain(Game &game, sf::Font font);
	~Playagain();

	void update(Xbox360Controller& controller);
	void reset(); // reset every thing when player come to confirm screen
	void render(sf::RenderWindow &window);
private:
	Game *m_game;


	sf::Font m_font;
	sf::Text m_text[3];

	sf::Texture m_texture;
	sf::Sprite m_SpriteA;
	sf::Sprite m_SpriteB;

	bool m_confirm; // check player selection
	bool m_button_released; // chenk player release A button
	bool m_reset_check;
};

#endif