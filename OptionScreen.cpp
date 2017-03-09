#include "OptionScreen.h"
#include <iostream>

//Slider* animationSpeed = new Slider("Animation Frames", nullptr);

Option::Option(Game & game, sf::Font font) :
	m_game(&game),
	m_Impact(font)
{

	m_textMessage[0].setPosition(850, 100);//set position
	m_textMessage[0].setString("Start Game");//set text
	m_textMessage[0].setFont(m_Impact);//set font 
	m_textMessage[0].setColor(sf::Color::Yellow);//set colour

	m_textMessage[1].setPosition(850, 175);//set position
	m_textMessage[1].setString("Settings");//set text
	m_textMessage[1].setFont(m_Impact);//set font 
	m_textMessage[1].setColor(sf::Color::Yellow);//set colour

	m_textMessage[2].setPosition(850, 250);//set position
	m_textMessage[2].setString("Quit");//set text
	m_textMessage[2].setFont(m_Impact);//set font 
	m_textMessage[2].setColor(sf::Color::Yellow);//set colour

	for (int i = 0; i < 2; i++)
	{
		settingButton[i].setSize(sf::Vector2f(20, 20));
		settingButton[i].setFillColor(sf::Color::Red);
	}
	settingButton[0].setPosition(200, 150);//positioning settings 
	settingButton[1].setPosition(200, 250);



	if (!m_Texture[0].loadFromFile("G:/jp-team-a/resource/images/selector.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[2].loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/circlemover.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[1].loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/Bar.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture[3].loadFromFile("G:/jp-team-a/resource/images/OptionScreen.jpg"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_Sprite[0].setTexture(m_Texture[0]);
	m_Sprite[0].setPosition(800, 100);//set image position in relation to origin
	m_Sprite[1].setTexture(m_Texture[1]);
	m_Sprite[1].setPosition(270, 400);
	m_Sprite[2].setTexture(m_Texture[2]);
	m_Sprite[2].setPosition(270, 400);
	m_Sprite[3].setTexture(m_Texture[3]);



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
	if (controller.m_currentState.Back)
	{

		options = true;
		strtgame = false;
		quitGame = false;
		controller.m_previousState = controller.m_currentState;


		closeWindow = true;

	}

	if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
	{

		options = false;
		strtgame = false;
		quitGame = true;

		if (button_ID < 2)
		{
			button_ID= button_ID +1;
		}
		else
		{
			button_ID = 0;
		}

	}


	if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
	{

		options = false;
		strtgame = true;
		quitGame = false;

		if (button_ID > 0)
		{
			button_ID--;
		}
		else
		{
			button_ID = 3;
		}

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
	if (controller.m_currentState.B && settings == true)
	{
		settings = false;//back out of settings
	}
	if (controller.m_currentState.DPadRight && settings == true)
	{

	}
	if (controller.m_currentState.DPadLeft && settings == true)
	{

	}

	if (button_ID == 0)
	{
		m_Sprite[0].setPosition(800, 100);
		controller.m_previousState = controller.m_currentState;
		strtgame = true;
		options = false;
		quitGame = false;
	}
	else if (button_ID == 1)
	{
		m_Sprite[0].setPosition(800, 175);
		controller.m_previousState = controller.m_currentState;
		options = true;
		strtgame = false;
		quitGame = false;
	}
	else if (button_ID == 2)
	{
		m_Sprite[0].setPosition(800, 250);
		controller.m_previousState = controller.m_currentState;
		quitGame = true;
		options = false;
		strtgame = false;
	}

}

void Option::changeScreen()
{
	//m_game->SetGameState(GameState::none);//change to game
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



		Window.draw(m_Sprite[1]);
		Window.draw(m_Sprite[2]);//draw scroll bar

	}


	Window.display();
}