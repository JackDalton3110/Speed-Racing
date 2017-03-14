#pragma once
#ifndef UPGRADE
#define UPGRADE

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Game.h"

class Game;

class Upgrade
{
public:
	Upgrade(Game& game, sf::Font font, sf::Font font1);
	~Upgrade();
	void update(sf::Time time, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);

private:
	void backOut();
	void drawStatusShape(sf::RenderWindow &window, int maxSpeed, int acceleration, int handling);
	int status_ID = 0; 

	void changeScreen();
	void backOut();
	int button_ID = 0;
	int setting_ID = 0;

	Game *m_game;
	sf::Text m_textMessage[10];//text
	sf::Font m_Motor;//font
	sf::Font m_HARLOW;
	sf::Texture m_texture[8];//background texture
	sf::Sprite m_Sprite[8];//sprite for texture

	int whiteCar_status[3] = { 0,0,0 };
	int redCar_status[3] = { 0,0,0 }; 
	int yellowCar_status[3] = { 0,0,0 };
	int greenCar_status[3] = { 0,0,0 };
	// array 0 for max speed, 1 for aceeleration, 2 for handling

	float whiteCar_values[3] = { 100, 4.2f, 50 };
	float reaCar_values[3] = { 90, 3.9f, 55 };
	float yellowCar_values[3] = { 98, 4.5f, 25 };
	float greenCar_values[3] = { 94, 4.0f, 30 };
	// array 0 for max speed, 1 for aceeleration, 2 for handling

	sf::RectangleShape Max_speed_shape[4];
	sf::RectangleShape Acceleration_shape[4];
	sf::RectangleShape Handling_shape[4];
	sf::RectangleShape m_selecter;

	bool m_status;
	bool button_released;

	std::string intToString(float num); // int to string
};

#endif