#include "OptionScreen.h"
#include <iostream>

Option::Option(Game & game, sf::Font font, sf::Font font2) :
	m_game(&game),
	m_Impact(font),
	m_Harlow(font2)

{

	m_textMessage[0].setPosition(830, 100);//set position
	m_textMessage[0].setString("Start Game");//set text
	m_textMessage[0].setFont(m_Harlow);//set font 
	m_textMessage[0].setColor(sf::Color::Black);//set colour

	m_textMessage[1].setPosition(830, 175);//set position
	m_textMessage[1].setString("Settings");//set text
	m_textMessage[1].setFont(m_Harlow);//set font 
	m_textMessage[1].setColor(sf::Color::Black);//set colour

	m_textMessage[2].setPosition(830, 250);//set position
	m_textMessage[2].setString("Quit");//set text
	m_textMessage[2].setFont(m_Harlow);//set font 
	m_textMessage[2].setColor(sf::Color::Black);//set colour

	
	
	settingButton[2].setSize(sf::Vector2f(780, 500));
	settingButton[2].setPosition(100, 100);
	settingButton[2].setFillColor(sf::Color(96, 96, 96));

	if (!m_Texture[0].loadFromFile("images/selector.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[2].loadFromFile("images/circlemover.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[1].loadFromFile("images/Bar.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[3].loadFromFile("images/OptionScreen.jpg"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_Sprite[0].setTexture(m_Texture[0]);
	m_Sprite[0].setPosition(780, 100);//set image position in relation to origin
	m_Sprite[1].setTexture(m_Texture[1]);
	m_Sprite[1].setPosition(270, 400);
	m_Sprite[2].setTexture(m_Texture[2]);
	m_Sprite[2].setPosition(270, 400);
	m_Sprite[3].setTexture(m_Texture[3]);


	m_textMessage[3].setString("Sound");//settings message
	m_textMessage[3].setPosition(300, 140);//set position
	m_textMessage[3].setFont(m_Impact);//set font 
	m_textMessage[3].setCharacterSize(100);
	m_textMessage[3].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[4].setString("Difficulty");//setting message
	m_textMessage[4].setPosition(300, 240);//set position
	m_textMessage[4].setFont(m_Impact);//set font
	m_textMessage[4].setCharacterSize(100);
	m_textMessage[4].setColor(sf::Color(255, 255, 255));//set color

	m_textMessage[5].setString("Help");
	m_textMessage[5].setPosition(300, 340);//set position
	m_textMessage[5].setFont(m_Impact);//set font 
	m_textMessage[5].setCharacterSize(100);
	m_textMessage[5].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[6].setString("SPEED");
	m_textMessage[6].setPosition(500, 1);
	m_textMessage[6].setStyle(sf::Text::Underlined);
	m_textMessage[6].setFont(m_Impact);
	m_textMessage[6].setCharacterSize(100);
	m_textMessage[6].setColor(sf::Color::Red);

}

Option::~Option()
{
	std::cout << "Destroying Option Screen" << std::endl;

}

void Option::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	if (controller.m_currentState.Back)
	{
		closeWindow = true;
	}

	if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
	{
		if (button_ID < 2)
		{
			button_ID = button_ID + 1;
		}
		else
		{
			button_ID = 0;
		}
	}


	if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
	{
		if (button_ID > 0)
		{
			button_ID--;
		}
		else
		{
			button_ID = 2;
		}
	}

	if (settings == true)
	{
		if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
		{
			if (button_ID < 2)
			{
				button_ID = button_ID + 1;
			}
			else
			{
				button_ID = 0;
			}
		}


		if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
		{
			if (button_ID > 0)
			{
				button_ID--;
			}
			else
			{
				button_ID = 2;
			}
		}
	}
	if (controller.m_currentState.A && quitGame == true && !controller.m_previousState.A)
	{
		closeGame = true;//close window
	}
	if (controller.m_currentState.A && strtgame == true &&!controller.m_previousState.A)
	{
		changeScreen();//change to game 
	}
	if (options == true && controller.m_currentState.A)
	{
		settings = true;//draw settings
		if (settings == true)
		{
			button_ID = 2;
		}
	}
	if (controller.m_currentState.B && settings == true && !controller.m_previousState.A)
	{
		settings = false;//back out of settings
		button_ID = 1;
	}

	if (button_ID == 0)
	{
		m_Sprite[0].setPosition(780, 100);
		controller.m_previousState = controller.m_currentState;
		strtgame = true;
		options = false;
		quitGame = false;
	}
	else if (button_ID == 1)
	{
		m_Sprite[0].setPosition(780, 175);
		controller.m_previousState = controller.m_currentState;
		options = true;
		strtgame = false;
		quitGame = false;
	}
	else if (button_ID == 2)
	{
		m_Sprite[0].setPosition(780, 250);
		controller.m_previousState = controller.m_currentState;
		quitGame = true;
		options = false;
		strtgame = false;
	}

	if (settings == true)//within settings menu
	{
		quitGame = false;
		options = false;
		strtgame = false;

		if (button_ID == 2)
		{
			m_Sprite[0].setPosition(275, 190);
			controller.m_previousState = controller.m_currentState;
			sound = true;
			difficulty = false;
		}

		else if (button_ID == 1)
		{
			m_Sprite[0].setPosition(275, 290);
			controller.m_previousState = controller.m_currentState;
			sound = false;
			difficulty = true;
		}
		else if (button_ID == 0)
		{
			m_Sprite[0].setPosition(275, 390);
			controller.m_previousState = controller.m_currentState;
		}
		if (controller.m_currentState.A && !controller.m_previousState.A && button_ID == 2)
		{
			changeToSound();
		}

		if (controller.m_currentState.A && !controller.m_previousState.A && button_ID == 1)
		{
			changeToDifficulty();
		}
	}

}

void Option::changeScreen()
{
	m_game->SetGameState(GameState::carSelect);//change to game
}
void Option::changeToOption()
{
	m_game->SetGameState(GameState::option);//settings
}
void Option::changeToSound()
{
	m_game->SetGameState(GameState::sound);
}

void Option::changeToDifficulty()
{
	m_game->SetGameState(GameState::Difficulty);
}

void Option::render(sf::RenderWindow & Window)
{

	Window.clear(sf::Color(0, 0, 1));//different from standards black
	Window.draw(m_Sprite[3]);
	Window.draw(m_textMessage[6]);

	if (settings != true)
	{
		Window.draw(m_Sprite[0]);
		Window.draw(m_textMessage[0]);
		Window.draw(m_textMessage[1]);
		Window.draw(m_textMessage[2]);//main menu draw

		if (closeGame == true)
		{
			Window.close();//quit game
		}
	}

	if (settings == true)
	{
		Window.draw(settingButton[2]);
		Window.draw(m_textMessage[3]);
		Window.draw(m_textMessage[4]);
		Window.draw(m_textMessage[5]);//setting draw 
		Window.draw(m_Sprite[0]);
	}


	Window.display();
}