#include "OptionScreen.h"
#include <iostream>

//Slider* animationSpeed = new Slider("Animation Frames", nullptr);

Option::Option(Game & game, sf::Font font) :
	m_game(&game),
	m_Impact(font)
{

	m_textMessage[0].setPosition(150, 250);//set position
	

}

Option::~Option()
{
	std::cout << "Destroying Splash Screen" << std::endl;

}

void Option::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	
	

}

void Option::changeScreen()
{
	m_game->SetGameState(GameState::none);
}
void Option::changeToOption()
{
	m_game->SetGameState(GameState::option);
}

void Option::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color(0, 0, 1));//different from standards black
	if(settings!=true)
	{
		
		Window.draw(m_textMessage[0]);
		
		if (closeGame == true)
		{
			Window.close();
		}
	}
	if (settings == true)
	{
		for (int i = 0; i < 2; i++)
		{
			Window.draw(settingButton[i]);
		}
	}
	

	Window.display();
}
