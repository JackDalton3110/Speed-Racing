#pragma once
#ifndef CONFIRM
#define CONFIRM

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Controller.h"

class Game;

class Confirm
{
public:
	Confirm(Game &game, sf::Font font);
	~Confirm();

	void update(Xbox360Controller& controller);
	void reset(); // reset every thing when player come to confirm screen
	void render(sf::RenderWindow &window);
private:
	Game *m_game;


	sf::Font m_font;
	sf::Text m_text[3];

	sf::Texture m_texture;
	sf::Sprite m_Sprite;

	bool m_confirm; // check player selection
	bool m_button_released; // chenk player release A button
	bool m_reset_check; 
};

#endif