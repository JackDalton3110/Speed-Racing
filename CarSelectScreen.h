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
	CarSelect(Game &game, sf::Font font, sf::Font font1);
	~CarSelect();
	void update(sf::Time time, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);
	void reset();
	void changeScreen();
	bool carSelected = false;
	int button_ID = 0;

	int getSelection_ID();

	void getCarValues(float white, float red, float yellow, float green, int i);

private:

	sf::Font m_Font;
	sf::Texture m_texture[6];
	sf::Sprite m_Sprite[6];

	sf::RectangleShape settingButton[5];

	sf::Font m_HARLOW;//font
	sf::Font m_Motor;//font
	sf::Text m_textMessage[8];//text

	Game *m_game;

	bool reset_check;
	bool m_button_released;

	float whiteCar_values[3];
	float reaCar_values[3];
	float yellowCar_values[3];
	float greenCar_values[3];
};
#endif // !CAR_SELECTION
