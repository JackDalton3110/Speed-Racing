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
#include "Player.h"
#include "Game.h"

class Game;

class Player;

class Map
{
public:

	Map(Game& game, Player & player);
	~Map();
	void update();
	void render(sf::RenderWindow& window);
	void collision();

private:

	Game *m_game;
	Player & m_player;
	sf::Sprite m_sprites[16];//sprite for texture(16)
	sf::Sprite m_outerSprites[16]; //sprites for the outer ring of the map
	sf::Texture m_outerTexture; //texture for the outer ring of the map
	sf::Texture m_textures[16]; //textures for the map (16)
	sf::Text m_textmsgX;
	sf::Text m_textmsgY;
	sf::Image m_image;
	int m_count;
	int m_counter;

	//Used for collision detection
	sf::Vector2f m_findTile;

};

#endif // !MAP