#include "Credits.h"
#include <iostream>
#include <fstream>

Credits::Credits(Game & game, sf::Font font, sfe::Movie movie) : 
	m_game(&game),
	m_impact(font),m_movie(movie),
	m_credits()
	
{
	std::ifstream creditsFile;
	creditsFile.open("Credits.txt");
	m_credits.setPosition(100.0f, 750.0f);
	m_credits.setFont(m_impact);

	while (!creditsFile.eof() && creditsFile.is_open())
	{
		std::getline(creditsFile, textline);
		m_credits.setString(m_credits.getString() + textline + "\n");
		m_credits.setColor(sf::Color(255, 255, 255));
	}

	if (!shader.loadFromFile("credits.frag", sf::Shader::Fragment))
	{
		std::string s("error loading shader");
		//throw std::exception(s.c_str);
	}
	shader.setParameter("time", 0);
	shader.setParameter("resolution", 1000, 800);

	if (!shaderTxt.loadFromFile("images/shaderTxt.png"))
	{
		std::string s("error loading shader texture");
		//throw std::exception(s.c_str);
	}
	shaderSprite.setTexture(shaderTxt);
	shaderSprite.setPosition(0, 0);



	m_movie.play();
	m_movie.scale(1.5f,1.25f);
}

Credits::~Credits()
{
	std::cout << "desturcting Credits" << std::endl;
}

void Credits::update(sf::Time deltaTime)
{
	m_movie.update();
	m_cumulativeTime += deltaTime;
	updateShader = m_cumulativeTime.asSeconds();
	shader.setParameter("time", updateShader);

	if (m_cumulativeTime.asSeconds() > 3)
	{
		endMovie = true;
	}

	if (m_cumulativeTime.asSeconds() > 19)
	{
		closeGame = true;
	}

	m_credits.move(0, -2);
}

void Credits::changeScreen()
{
	m_game->SetGameState(GameState::credits);
}

void Credits::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0));
	window.draw(m_movie);
	if (endMovie == true)
	{
		window.draw(shaderSprite, &shader);
		window.draw(m_credits);
	}
	if (closeGame == true)
	{
		window.close();
	}
}