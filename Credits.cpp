#include "Credits.h"
#include <iostream>
#include <fstream>

Credits::Credits(Game & game, sf::Font font) :
	m_game(&game),
	m_impact(font),
	m_credits()
{
	std::ifstream creditsFile;
	creditsFile.open("G:/HCI/button-game-jack-jamie-1/ButtonGameCredits.txt");
	m_credits.setPosition(100.0f, 350.0f);
	m_credits.setFont(m_impact);

	while (!creditsFile.eof() && creditsFile.is_open())
	{
		std::getline(creditsFile, textline);
		m_credits.setString(m_credits.getString() + textline + "\n");
		m_credits.setColor(sf::Color(255, 255, 255));
	}
}

Credits::~Credits()
{
	std::cout << "desturcting Credits" << std::endl;
}

void Credits::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;

	m_credits.move(0, -5);
}

void Credits::changeScreen()
{
	m_game->SetGameState(GameState::credits);
}

void Credits::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0));
	window.draw(m_credits);
	window.display();

}