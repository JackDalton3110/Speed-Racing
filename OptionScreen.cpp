#include "OptionScreen.h"
#include <iostream>

Option::Option(Game & game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_Motor(font),
	m_HARLOW(font1)

{

	m_textMessage[0].setPosition(830, 100);//set position
	m_textMessage[0].setString("Start Game");//set text
	m_textMessage[0].setFont(m_HARLOW);//set font 
	m_textMessage[0].setColor(sf::Color::Black);//set colour

	m_textMessage[1].setPosition(830, 150);//set position
	m_textMessage[1].setString("Settings");//set text
	m_textMessage[1].setFont(m_HARLOW);//set font 
	m_textMessage[1].setColor(sf::Color::Black);//set colour

	m_textMessage[2].setPosition(830, 200);//set position
	m_textMessage[2].setString("Upgrade");//set text
	m_textMessage[2].setFont(m_HARLOW);//set font 
	m_textMessage[2].setColor(sf::Color::Black);//set colour

	m_textMessage[7].setPosition(830, 250);//set position
	m_textMessage[7].setString("Quit");//set text
	m_textMessage[7].setFont(m_HARLOW);//set font 
	m_textMessage[7].setColor(sf::Color::Black);//set colour


	if (!m_Texture[0].loadFromFile("images/selector.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[3].loadFromFile("images/OptionScreen.jpg"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!m_Texture[4].loadFromFile("images/template.png"))
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
	m_Sprite[4].setTexture(m_Texture[4]);
	m_Sprite[4].setPosition(270, 175);
	m_Sprite[5].setTexture(m_Texture[4]);
	m_Sprite[5].setPosition(270, 300);
	m_Sprite[6].setTexture(m_Texture[4]);
	m_Sprite[6].setPosition(270, 425);

	m_textMessage[3].setString("Audio");//settings message
	m_textMessage[3].setPosition(350, 140);//set position
	m_textMessage[3].setFont(m_Motor);//set font 
	m_textMessage[3].setCharacterSize(100);
	m_textMessage[3].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[4].setString("Difficulty");//setting message
	m_textMessage[4].setPosition(300, 275);//set position
	m_textMessage[4].setFont(m_Motor);//set font
	m_textMessage[4].setCharacterSize(100);
	m_textMessage[4].setColor(sf::Color(255, 255, 255));//set color

	m_textMessage[5].setString("Help");
	m_textMessage[5].setPosition(360, 400);//set position
	m_textMessage[5].setFont(m_Motor);//set font 
	m_textMessage[5].setCharacterSize(100);
	m_textMessage[5].setColor(sf::Color(255, 255, 255));//set colour

	m_textMessage[6].setString("SPEED");
	m_textMessage[6].setPosition(450, -50);
	m_textMessage[6].setFont(m_Motor);
	m_textMessage[6].setCharacterSize(150);
	m_textMessage[6].setColor(sf::Color::Red);

}

Option::~Option()
{
	std::cout << "Destroying Splash Screen" << std::endl;

}

void Option::update(sf::Time deltaTime, Xbox360Controller& controller)
{


	if (controller.m_currentState.Back)
	{
		closeWindow = true;
	}

	if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
	{
		if (button_ID < 3)
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
			button_ID = 3;
		}
	}

	if (settings == true)
	{
		if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
		{
			if (setting_ID < 2)
			{
				setting_ID = setting_ID + 1;
			}
			else
			{
				setting_ID = 0;
			}
		}


		if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
		{
			if (setting_ID > 0)
			{
				setting_ID--;
			}
			else
			{
				setting_ID = 2;
			}
		}
	}
	if (controller.m_currentState.A && quitGame == true && !controller.m_previousState.A)
	{
		closeGame = true;//close window
	}
	if (controller.m_currentState.A && strtgame == true )
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
	if (controller.m_currentState.DPadRight && settings == true)
	{
		if (m_Sprite[2].getPosition().x <= 490 && m_Sprite[2].getPosition().x >= 260)
		{
			m_Sprite[2].move(0.5, 0);//move slider right
		}

	}
	if (controller.m_currentState.DPadLeft && settings == true)
	{
		if (m_Sprite[2].getPosition().x <= 500 && m_Sprite[2].getPosition().x >= 260)
		{
			m_Sprite[2].move(-0.5, 0);//move slider left
		}

	}

	if (button_ID == 0)
	{
		m_Sprite[0].setPosition(780, 100);
		controller.m_previousState = controller.m_currentState;
		strtgame = true;
		options = false;
		upgrade = false;
		quitGame = false;
	}
	else if (button_ID == 1)
	{
		m_Sprite[0].setPosition(780, 150);
		controller.m_previousState = controller.m_currentState;
		strtgame = false;
		options = true;
		upgrade = false;
		quitGame = false;
	}
	else if (button_ID == 2)
	{
		m_Sprite[0].setPosition(780, 200);
		controller.m_previousState = controller.m_currentState;
		strtgame = false;
		options = false;
		upgrade = true;
		quitGame = false;
	}
	else if (button_ID == 3)
	{
		m_Sprite[0].setPosition(780, 250);
		controller.m_previousState = controller.m_currentState;
		strtgame = false;
		options = false;
		upgrade = false;
		quitGame = true;
	}

	if (settings == true)
	{
		strtgame = false;
		options = false;
		upgrade = false;
		quitGame = false;

		if (setting_ID == 0)
		{
			m_Sprite[0].setPosition(275, 200);
			controller.m_previousState = controller.m_currentState;
		}

		else if (setting_ID == 1)
		{
			m_Sprite[0].setPosition(275, 325);
			controller.m_previousState = controller.m_currentState;
		}
		else if (setting_ID == 2)
		{
			m_Sprite[0].setPosition(275, 465);
			controller.m_previousState = controller.m_currentState;
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

void Option::render(sf::RenderWindow & Window)
{

	Window.clear(sf::Color(0, 0, 1));//different from standards black
	Window.draw(m_Sprite[3]);

	if (settings != true)
	{
		Window.draw(m_Sprite[0]);
		Window.draw(m_textMessage[0]);
		Window.draw(m_textMessage[1]);
		Window.draw(m_textMessage[2]);//main menu draw
		Window.draw(m_textMessage[7]);//setting draw 
		Window.draw(m_textMessage[6]);

		if (closeGame == true)
		{
			Window.close();
		}
	}

	if (settings == true)
	{

		Window.draw(m_Sprite[4]);
		Window.draw(m_Sprite[5]);
		Window.draw(m_Sprite[6]);
		Window.draw(settingButton[2]);
		Window.draw(m_textMessage[3]);
		Window.draw(m_textMessage[4]);
		Window.draw(m_textMessage[5]);//setting draw 
		Window.draw(m_Sprite[0]);
	}


	Window.display();
}