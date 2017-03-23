#pragma once
#ifndef SPLASH
#define SPLASH
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Controller.h"

class Game;

class Splash
{
public:
	Splash(Game& game, sf::Font font, sf::Font font1);
	~Splash();
	//methods for Splash
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void changeScreen();
	bool change = false;
	int alpha = 255;

private:
	Game *m_game;
	float updateShader;
	sf::Shader shader;
	sf::Texture shaderTxt;
	sf::Sprite shaderSprite;
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
