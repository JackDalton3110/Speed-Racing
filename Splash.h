#pragma once
#ifndef SPLASH
#define SPLASH
#include <SFML\Graphics.hpp>
#include "Game.h"

class Game;

class Splash
{
public:
	Splash(Game& game, sf::Font font, sf::Font font1);
	~Splash();
	//methods for Splash
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void rollCredits();//starts credits 
	void changeScreen();

private:
	Game *m_game;
	bool drawTime = false;//draw text when true  
	bool credits = false;//bool for changing screen
	sf::Time m_cumulativeTime;//time
	sf::Font m_HARLOW;//font
	sf::Font m_Motor;//font
	sf::Text m_textMessage;//text
	sf::Text m_textMessage1;//text
	sf::Texture m_Texture;//background texture
	sf::Sprite m_Sprite;//sprite for texture
	sf::Event event;

};
#endif // !SPLASH
