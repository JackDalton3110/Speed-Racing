#pragma once
#ifndef CAR_SELECTION
#define CAR_SELECTION

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Game.h"

class Game;

class CarSelect
{
public:
	CarSelect(Game &game,sf::Font font);
	~CarSelect();
	void update(sf::Time time, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);
	void changeScreen();
	bool carSelected = false;
	int button_ID = 0;

	int getSelection_ID();
private:
	sf::Font m_Font;
	sf::Texture carText[4];
	sf::Sprite carSprite[4];
	sf::Texture selectTxt;
	sf::Sprite selectSprite;
	sf::Sprite backgrndSprite;
	sf::Texture backgrndTxt;
	Game *m_game;

};
#endif // !CAR_SELECTION
