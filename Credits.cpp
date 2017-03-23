#include "Credits.h"
#include <iostream>
#include <fstream>

Credits::Credits(Game & game, sf::Font font, sfe::Movie movie) : 
	m_game(&game),
	m_impact(font),
	m_credits() 
	
{
	std::ifstream creditsFile;
	creditsFile.open("Credits.txt");
	m_credits.setPosition(100.0f, 750.0f);
	m_credits.setFont(m_impact);

	if (!m_movie.openFromFile("Video/animation4.mov"))
	{
		//loads movie 
		std::string s("error loading mov file");
		throw std::exception(s.c_str());
	}
	//stops movie
	m_movie.stop();
	while (!creditsFile.eof() && creditsFile.is_open())
	{
		//loads text file for credits
		std::getline(creditsFile, textline);
		m_credits.setString(m_credits.getString() + textline + "\n");
		m_credits.setColor(sf::Color(255, 255, 255));
	}

	if (!shader.loadFromFile("credits.frag", sf::Shader::Fragment))
	{
		//loads shader form .frag file
		std::string s("error loading shader");
		//throw std::exception(s.c_str);
	}
	//set parameters for shader
	shader.setParameter("time", 0);
	shader.setParameter("resolution", 1000, 800);

	if (!shaderTxt.loadFromFile("images/shaderTxt.png"))
	{
		//loads blank texture for shader
		std::string s("error loading shader texture");
		//throw std::exception(s.c_str);
	}
	//set texture to sprite
	shaderSprite.setTexture(shaderTxt);
	shaderSprite.setPosition(0, 0);

	//play and scale video	
	m_movie.play();
	m_movie.scale(1.5f, 1.25f);
	
}

Credits::~Credits()
{
	std::cout << "desturcting Credits" << std::endl;
}

void Credits::update(sf::Time deltaTime)
{
	//if the movie isn't playing, play
	if (m_movie.getStatus() != sfe::Playing)
	{
		m_movie.play();
	}
	//update movie
	m_movie.update();
	m_cumulativeTime += deltaTime;
	//update shader
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

	m_game->SetGameState(GameState::option);
}

void Credits::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0));
	window.draw(m_movie);
	if (endMovie == true)
	{
		//draw shader after movie ends
		window.draw(shaderSprite, &shader);
		window.draw(m_credits);
	}
	if (closeGame == true)
	{
		window.close();
	}
}