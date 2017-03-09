#include "OptionScreen.h"
#include <iostream>

//Slider* animationSpeed = new Slider("Animation Frames", nullptr);

Option::Option(Game & game, sf::Font font) :
	m_game(&game),
	m_Impact(font)
{

	m_textMessage[0].setPosition(150, 250);//set position
	m_textMessage[0].setString("Start Game");//set text
	m_textMessage[0].setFont(m_Impact);//set font 
	m_textMessage[0].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[1].setPosition(400, 250);//set position
	m_textMessage[1].setString("Settings");//set text
	m_textMessage[1].setFont(m_Impact);//set font 
	m_textMessage[1].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[2].setPosition(300, 350);//set position
	m_textMessage[2].setString("Quit");//set text
	m_textMessage[2].setFont(m_Impact);//set font 
	m_textMessage[2].setColor(sf::Color(255, 255, 255));//set colour

	for (int i = 0; i < 2; i++)
	{
		settingButton[i].setSize(sf::Vector2f(20, 20));
		settingButton[i].setFillColor(sf::Color::Red);
	}
	settingButton[0].setPosition(200, 150);//positioning settings 
	settingButton[1].setPosition(200, 250);


	m_textMessage[3].setString("sound");//settings message
	m_textMessage[3].setPosition(120, 140);//set position
	m_textMessage[3].setFont(m_Impact);//set font 
	m_textMessage[3].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[4].setString("FX");//setting message
	m_textMessage[4].setPosition(165, 240);//set position
	m_textMessage[4].setFont(m_Impact);//set font 
	m_textMessage[4].setColor(sf::Color(255, 255, 255));//set color

	m_textMessage[5].setString("Volume");
	m_textMessage[5].setPosition(120, 340);//set position
	m_textMessage[5].setFont(m_Impact);//set font 
	m_textMessage[5].setColor(sf::Color(255, 255, 255));//set colour


}

Option::~Option()
{
	std::cout << "Destroying Splash Screen" << std::endl;

}

void Option::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	if (controller.m_currentState.DPadRight)
	{
		options = true;
		strtgame = false;
		quitGame = false;
		controller.m_previousState = controller.m_currentState;

	}
	if (controller.m_currentState.DPadDown)
	{
		options = false;
		strtgame = false;
		quitGame = true;
	}

	if (controller.m_currentState.DPadLeft)
	{
		options = false;
		strtgame = true;
		quitGame = false;
	}
	if (controller.m_currentState.A && quitGame == true)
	{
		closeGame = true;//close window
	}
	if (controller.m_currentState.A && strtgame == true)
	{
		changeScreen();//change to game 
	}
	if (options == true && controller.m_currentState.A)
	{
		settings = true;//draw settings
	}
	if (controller.m_currentState.B&&settings == true)
	{
		settings = false;//back out of settings
	}
	if (controller.m_currentState.DPadRight && settings == true)
	{

	}
	if (controller.m_currentState.DPadLeft && settings == true)
	{

	}


}

void Option::changeScreen()
{
	m_game->SetGameState(GameState::none);//change to game
}
void Option::changeToOption()
{
	m_game->SetGameState(GameState::option);//settings
}

void Option::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color(0, 0, 1));//different from standards black
	if (settings != true)
	{
		Window.draw(m_textMessage[0]);
		Window.draw(m_textMessage[1]);
		Window.draw(m_textMessage[2]);//main menu draw
		if (closeGame == true)
		{
			Window.close();
		}
	}

	if (settings == true)
	{
		Window.draw(m_textMessage[3]);
		Window.draw(m_textMessage[4]);
		Window.draw(m_textMessage[5]);//setting draw 
		for (int i = 0; i < 2; i++)
		{
			Window.draw(settingButton[i]);
		}
	}


	Window.display();
}