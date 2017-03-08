#pragma once
#ifndef LICENCE
#define LICENCE

#include <SFML\Graphics.hpp>
#include "Game.h"

class Game;

class Licence
{
public:
	Licence(Game& game, sf::Font font);
	~Licence();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);

private:
	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Font m_Impact;
	sf::Text m_textMessage;
	sf::Text m_textMessage1;
	sf::Texture m_Texture;//bullet texture
	sf::Sprite m_Sprite;//bullet for texture
};
#endif 