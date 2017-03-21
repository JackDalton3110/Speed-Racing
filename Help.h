/// <summary>
/// Conor O'Toole 13/03/17 14::00 - 
/// 
/// </summary>
#pragma once
#ifndef HELP
#define HELP
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Controller.h"
#include <fstream>
class Game;

class Help
{
public:
	Help(Game & game, sf::Font font);
	~Help();
	void update(Xbox360Controller &controller);
	void render(sf::RenderWindow& window);

private:

	Game *m_game;

	//array for managing text object
	sf::Text m_txtArray;

	//instructions text
	sf::Text m_line1;
	sf::Text m_line2;
	sf::Text m_line3;
	sf::Text m_line4;
	sf::Text m_line5;
	std::string m_analogString;

	//Font
	sf::Font m_helpFont;
	
	//instructions images
	sf::Sprite m_controllerSprite;
	sf::Texture m_texture;
	sf::RectangleShape m_line;
	
};

#endif // !Help