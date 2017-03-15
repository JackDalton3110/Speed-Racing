#include "Upgrade.h"

Upgrade::Upgrade(Game &game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_HARLOW(font),
	m_Motor(font1)
{
	if (!m_texture[0].loadFromFile("images/whiteCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_texture[1].loadFromFile("images/redCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_texture[2].loadFromFile("images/yellowCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_texture[3].loadFromFile("images/greenCarSprite.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}

	m_Sprite[0].setTexture(m_texture[0]);
	m_Sprite[1].setTexture(m_texture[1]);
	m_Sprite[2].setTexture(m_texture[2]);
	m_Sprite[3].setTexture(m_texture[3]);
	m_Sprite[4].setTexture(m_texture[4]);
	m_Sprite[0].setPosition(325, 0);
	m_Sprite[1].setPosition(325, 200);
	m_Sprite[2].setPosition(325, 400);
	m_Sprite[3].setPosition(325, 600);
	m_Sprite[0].setRotation(90);
	m_Sprite[1].setRotation(90);
	m_Sprite[2].setRotation(90);
	m_Sprite[3].setRotation(90);
	m_Sprite[3].setRotation(90);


	m_textMessage[0].setPosition(700, 200);//set position
	m_textMessage[0].setString("Max Speed");//set text
	m_textMessage[0].setFont(m_HARLOW);//set font 
	m_textMessage[0].setColor(sf::Color::White);//set colour

	m_textMessage[1].setPosition(700, 400);//set position
	m_textMessage[1].setString("Aceleration");//set text
	m_textMessage[1].setFont(m_HARLOW);//set font 
	m_textMessage[1].setColor(sf::Color::White);//set colour

	m_textMessage[2].setPosition(700, 600);//set position
	m_textMessage[2].setString("Handling");//set text
	m_textMessage[2].setFont(m_HARLOW);//set font 
	m_textMessage[2].setColor(sf::Color::White);//set colour

	m_textMessage[3].setPosition(450, 0);//set position
	m_textMessage[3].setString("Upgrade");//set text
	m_textMessage[3].setFont(m_Motor);//set font 
	m_textMessage[3].setColor(sf::Color::Red);//set colour
	m_textMessage[3].setCharacterSize(110);

	// car varibles 
	//Max Speed
	m_textMessage[4].setPosition(700, 300);//set position
	m_textMessage[4].setFont(m_Motor);//set font 
	m_textMessage[4].setColor(sf::Color::Red);//set colour
											  //Aceleration
	m_textMessage[5].setPosition(700, 500);//set position
	m_textMessage[5].setFont(m_Motor);//set font 
	m_textMessage[5].setColor(sf::Color::Red);//set colour

	m_textMessage[6].setPosition(700, 700);//set position
	m_textMessage[6].setFont(m_Motor);//set font 
	m_textMessage[6].setColor(sf::Color::Red);//set colour

}

Upgrade::~Upgrade()
{
	std::cout << "destroying upgrade menu" << std::endl;
}

void Upgrade::update(sf::Time time, Xbox360Controller &controller)
{
	if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
	{
		if (button_ID<3)
		{
			button_ID++;
		}
		else
		{
			button_ID = 0;
		}
	}

	if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
	{
		if (button_ID>0)
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
		if (m_Sprite[0].getPosition().x < 450)//any key accepted to change screen to credits
		{
			m_Sprite[0].move(10, 0);
		}
		m_Sprite[1].setPosition(325, 200);
		m_Sprite[2].setPosition(325, 400);
		m_Sprite[3].setPosition(325, 600);
		m_textMessage[4].setString("100kph");//set Max Speed
		m_textMessage[5].setString("4.2 sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString("50%");//set Handling
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 1)
	{
		if (m_Sprite[1].getPosition().x < 450)//any key accepted to change screen to credits
		{
			m_Sprite[1].move(10, 0);
		}
		m_Sprite[0].setPosition(325, 0);
		m_Sprite[2].setPosition(325, 400);
		m_Sprite[3].setPosition(325, 600);
		m_textMessage[4].setString("90kph");//need to be changed to a player editable varible
		m_textMessage[5].setString("3.9 sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString("60%");//set Handling
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 2)
	{
		if (m_Sprite[2].getPosition().x < 450)//any key accepted to change screen to credits
		{
			m_Sprite[2].move(10, 0);
		}
		m_Sprite[0].setPosition(325, 0);
		m_Sprite[1].setPosition(325, 200);
		m_Sprite[3].setPosition(325, 600);
		m_textMessage[4].setString("98kph");
		m_textMessage[5].setString("4.5 sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString("30%");//set Handling
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 3)
	{
		if (m_Sprite[3].getPosition().x < 450)//any key accepted to change screen to credits
		{
			m_Sprite[3].move(10, 0);
		}
		m_Sprite[0].setPosition(325, 0);
		m_Sprite[1].setPosition(325, 200);
		m_Sprite[2].setPosition(325, 400);
		m_textMessage[4].setString("94kph");
		m_textMessage[5].setString("4.0 sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString("40%");//set Handling
		controller.m_previousState = controller.m_currentState;
	}

}

void Upgrade::changeScreen()
{
	m_game->SetGameState(GameState::upgrade);
	
}
void Upgrade::backOut()
{
	m_game->SetGameState(GameState::option);

}

void Upgrade::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0, 255));


	for (int i = 0; i < 4; i++)
	{
		window.draw(m_Sprite[i]);
	}

	window.draw(m_textMessage[0]);
	window.draw(m_textMessage[1]);
	window.draw(m_textMessage[2]);//main menu draw
	window.draw(m_textMessage[3]);//setting draw 
	window.draw(m_textMessage[4]);
	window.draw(m_textMessage[5]);
	window.draw(m_textMessage[6]);

	//window.display();
}
