#include "CarSelectScreen.h"

CarSelect::CarSelect(Game &game, sf::Font font):
	m_game(&game),
	m_Font(font)
{
	if (!carText[0].loadFromFile("images/whiteCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!carText[1].loadFromFile("images/redCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!carText[2].loadFromFile("images/yellowCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!carText[3].loadFromFile("images/greenCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!selectTxt.loadFromFile("images/arrow.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!backgrndTxt.loadFromFile("images/selectbkgr.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}

	carSprite[0].setTexture(carText[0]);
	carSprite[1].setTexture(carText[1]);
	carSprite[2].setTexture(carText[2]);
	carSprite[3].setTexture(carText[3]);
	carSprite[0].setPosition(125, 300);
	carSprite[1].setPosition(325, 300);
	carSprite[2].setPosition(550, 300);
	carSprite[3].setPosition(750, 300);
	selectSprite.setTexture(selectTxt);
	backgrndSprite.setTexture(backgrndTxt);

	

}

CarSelect::~CarSelect()
{
	std::cout << "destroying car select" << std::endl;
}

void CarSelect::update(sf::Time time, Xbox360Controller &controller)
{
	if (controller.m_currentState.DPadRight && !controller.m_previousState.DPadRight)
	{
		if(button_ID<3)
		{
			button_ID++;
		}
		else
		{
			button_ID = 0;
		}
	}

	if (controller.m_currentState.DPadLeft && !controller.m_previousState.DPadLeft)
	{
		if(button_ID>0)
		{
			button_ID--;
		}
		else
		{
			button_ID = 3;
		}
	}
	if (button_ID == 0)
	{
		selectSprite.setPosition(200, 250);
		controller.m_previousState = controller.m_currentState;	
	}
	else if (button_ID == 1)
	{
		selectSprite.setPosition(400, 250);
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 2)
	{
		selectSprite.setPosition(600, 250);
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 3)
	{
		selectSprite.setPosition(800, 250);
		controller.m_previousState = controller.m_currentState;
	}
	
}

void CarSelect::changeScreen()
{
	if (carSelected == true)
	{
		m_game->SetGameState(GameState::none);
	}
}

void CarSelect::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0, 255));
	window.draw(backgrndSprite);
	window.draw(selectSprite);

	for (int i = 0; i < 4; i++)
	{
		window.draw(carSprite[i]);
	}

	window.display();
}