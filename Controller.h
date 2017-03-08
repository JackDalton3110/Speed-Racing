#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>


struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DPadUp;
	bool DPadDown;
	bool DPadLeft;
	bool DPadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float RTrigger;
	float LTrigger;
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbSticks;
};

/// <summary>
/// Xbox controller class to query current state of the controller 
/// to mimic the cotroller states like XNA
/// </summary>


class Xbox360Controller
{
private:
	//deadzone for the dpad (really a joystick)
	const int dpadThreshold = 50;

public:
	//index count for multiple controllers if connected
	int sf_Joystick_index;
	//the current state of all buttons
	GamePadState m_currentState;
	//the previous state to use to check for the moment a button is pressed
	GamePadState m_previousState;

	Xbox360Controller();
	~Xbox360Controller();
	void Xbox360Controller::update();
	bool isConnected();
	bool connect();
};
#endif // !CONTROLLER_H
