#pragma once
#ifndef CREDITS
#define CREDITS
#include <SFML\Graphics.hpp>
#include "Game.h"
#include <fstream>
class Game;

class Credits
{
public:
	Credits(Game& game, sf::Font font);
	~Credits();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void changeScreen();

private:
	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Text m_credits;
	std::string textline;
	sf::Font m_impact;
	sf::Text m_textMessage;
	

};

#endif // !CREDITS
