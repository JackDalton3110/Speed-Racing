#pragma once
#ifndef XBOX360CONTROLLER
#define XBOX360CONTROLLER

#include <SFML/Graphics.hpp>
#include <string>

/// <summary>
/// data to store the current state of the controller
/// </summary>
struct GamePadstate
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadRight;
	bool DpadLeft;
	bool Start;
	bool Back;
	bool Xbox;
	float RTtigger;
	float LTtigger;
	sf::Vector2f RighThumbStick;
	sf::Vector2f LeftThumbStick;
};

/// <summary>
/// xbox controiller class to query current state of controller
/// to mimic the controller states like XNA
/// </summary>
class Xbox360Controller {
private:
	//deadzone for the dpad
	const int dpadThreshold = 50;
	
	sf::Font font;
	sf::Text text[20];

	GamePadstate state;
	std::string toString(float num); // convert number to string
public:
	// set text state
	void initSprites();
	// index count for multiple controllers if connected
	unsigned int sf_Joystick_index;
	// the current state of all the buttons
	GamePadstate m_currentState; 
	// the previous state to use to check for the moment a button is pressed
	GamePadstate m_previousState;

	bool Abutton();
	bool Bbutton();
	bool Xbutton();
	bool Ybutton();
	bool LBbutton();
	bool RBbutton();
	bool LeftThumbStickClickButton();
	bool RightThumbStickClickButton();
	bool DpadUpButton();
	bool DpadDownButton();
	bool DpadRightButton();
	bool DpadLeftButton();
	bool StartButton();
	bool BackButton();
	bool XboxButton();

	Xbox360Controller();
	~Xbox360Controller();
	void Xbox360Controller::update();
	bool isConnected();
	bool connect();

	void render(sf::RenderWindow & window); // draw text
	void CheckButton();
};

#endif // ! XBOX360CONTROLLER