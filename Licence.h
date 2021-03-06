#pragma once
#ifndef LICENCE
#define LICENCE

#include <SFML\Graphics.hpp>
#include "Game.h"

class Game;

class Licence
{
public:
	Licence(Game& game, sf::Font font, sf::Font font1);
	~Licence();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	int alpha = 0;

private:
	Game *m_game;
	float updateShader;
	sf::Shader shader;
	sf::Texture shaderTxt;
	sf::Sprite shaderSprite;
	sf::Time m_cumulativeTime;
	sf::Font m_HARLOW;
	sf::Font m_Motor;
	sf::Text m_textMessage;
	sf::Text m_textMessage1;
	sf::Texture m_Texture;//bullet texture
	sf::Sprite m_Sprite;//bullet for texture
};
#endif 