/// <summary>
/// @Author Conor O'Toole
/// 
///  Worked on
///  14/03/17 (19:30 - 21:50)
///  15/03/17 (9:20 - 10:35)
/// 
/// </summary>
#pragma once
#ifndef MAP
#define MAP
#include <SFML\Graphics.hpp>
#include "Game.h"

class Game;

class Player;

class Map
{
public:

	Map(Game& game);
	~Map();
	void update();
	void render(sf::RenderWindow& window);

private:

	Game *m_game;
	Player *m_player;
	sf::Sprite m_sprites[16];//sprite for texture(16)
	sf::Sprite m_outerSprites[16]; //sprites for the outer ring of the map
	sf::Texture m_outerTexture; //texture for the outer ring of the map
	sf::Texture m_textures[16]; //textures for the map (16)
	sf::Text m_textmsgX;
	sf::Text m_textmsgY;
	int m_count;
	int m_counter;

	// These floats are used for setting the positions
	// of the map tiles.
	float m_posYrowOne;
	float m_posYrowTwo;
	float m_posYrowThree;
	float m_posYrowFour;
};

#endif // !MAP