#include "Credits.h"
#include <iostream>
#include <fstream>

Credits::Credits(Game & game, sf::Font font, sfe::Movie movie) : 
	m_game(&game),
	m_impact(font),m_movie(movie),
	m_credits()
	
{
	std::ifstream creditsFile;
	creditsFile.open("G:/Credits.txt");
	m_credits.setPosition(100.0f, 350.0f);
	m_credits.setFont(m_impact);

	while (!creditsFile.eof() && creditsFile.is_open())
	{
		std::getline(creditsFile, textline);
		m_credits.setString(m_credits.getString() + textline + "\n");
		m_credits.setColor(sf::Color(255, 255, 255));
	}

	m_movie.play();
	m_movie.scale(1.25f,1.25f);
}

Credits::~Credits()
{
	std::cout << "desturcting Credits" << std::endl;
}

void Credits::update(sf::Time deltaTime)
{
	m_movie.update();
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
	window.draw(m_movie);
	window.draw(m_credits);
}