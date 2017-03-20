#include "Upgrade.h"

Upgrade::Upgrade(Game &game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_HARLOW(font),
	m_Motor(font1),
	m_size(600, 200),
	button_released(false),
	m_status(false)

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

	m_Sprite[0].setTexture(m_texture[0]); // white car
	m_Sprite[1].setTexture(m_texture[1]); // red car 
	m_Sprite[2].setTexture(m_texture[2]); // yellow car
	m_Sprite[3].setTexture(m_texture[3]); // green car 

	m_Sprite[0].setPosition(325, 0);
	m_Sprite[1].setPosition(325, 200);
	m_Sprite[2].setPosition(325, 400);
	m_Sprite[3].setPosition(325, 600);
	m_Sprite[0].setRotation(90);
	m_Sprite[1].setRotation(90);
	m_Sprite[2].setRotation(90);
	m_Sprite[3].setRotation(90);

	//m_Sprite[3].setRotation(90);

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
	
	//Handling
	m_textMessage[6].setPosition(700, 700);//set position
	m_textMessage[6].setFont(m_Motor);//set font 
	m_textMessage[6].setColor(sf::Color::Red);//set colour

	m_textMessage[7].setPosition(920, 340);//set position
	m_textMessage[7].setFont(m_Motor);//set font 
	m_textMessage[7].setColor(sf::Color::Red);//set colour
	m_textMessage[7].setString("MAX"); // set string

	m_textMessage[8].setPosition(920, 540);//set position
	m_textMessage[8].setFont(m_Motor);//set font 
	m_textMessage[8].setColor(sf::Color::Red);//set colour
	m_textMessage[8].setString("MAX"); // set string

	m_textMessage[9].setPosition(920, 740);//set position
	m_textMessage[9].setFont(m_Motor);//set font 
	m_textMessage[9].setColor(sf::Color::Red);//set colour
	m_textMessage[9].setString("MAX"); // set string

	m_textMessage[10].setFont(m_Motor);
	m_textMessage[10].setColor(sf::Color::Red);

	m_textMessage[11].setFont(m_Motor);
	m_textMessage[11].setColor(sf::Color::Red);
	m_textMessage[11].setString("Need 1 Scrap");

	for (int i = 0; i < 4; i++)
	{
		Max_speed_shape[i].setPosition(700 + i * 50, 340); // set positon
		Max_speed_shape[i].setSize(sf::Vector2f(50, 40)); // set size
		Max_speed_shape[i].setFillColor(sf::Color::Yellow); // set color
		Max_speed_shape[i].setOutlineThickness(5);
		Max_speed_shape[i].setOutlineColor(sf::Color::Blue);

		Acceleration_shape[i].setPosition(700 + i * 50, 540); // set positon
		Acceleration_shape[i].setSize(sf::Vector2f(50, 40)); // set size
		Acceleration_shape[i].setFillColor(sf::Color::Yellow); // set color
		Acceleration_shape[i].setOutlineThickness(5);
		Acceleration_shape[i].setOutlineColor(sf::Color::Blue);

		Handling_shape[i].setPosition(700 + i * 50, 740); // set positon
		Handling_shape[i].setSize(sf::Vector2f(50, 40)); // set size
		Handling_shape[i].setFillColor(sf::Color::Yellow); // set color
		Handling_shape[i].setOutlineThickness(5);
		Handling_shape[i].setOutlineColor(sf::Color::Blue);
	}

	m_selecter.setOutlineThickness(5);
	m_selecter.setOutlineColor(sf::Color::Blue);
	m_selecter.setFillColor(sf::Color::Black);
	m_selecter.setSize(sf::Vector2f(300, 200));

	warning_back.setOutlineThickness(5);
	warning_back.setOutlineColor(sf::Color::Red);
	warning_back.setFillColor(sf::Color::White);
	warning_back.setSize(m_size);
	warning_back.setOrigin(m_size.x / 2, m_size.y / 2);
	warning_back.setPosition(500, 400);

	m_textMessage[12].setFont(m_Motor);
	m_textMessage[12].setColor(sf::Color::Red);
	m_textMessage[12].setString("!! NOT ENOUGH SCRAP !! ");
	sf::FloatRect textRect = m_textMessage[12].getLocalBounds();
	m_textMessage[12].setOrigin(textRect.width / 2, textRect.height / 2);
	m_textMessage[12].setPosition(500, 400);

	if (!m_texture_scrap.loadFromFile("images/Scrap.png"))
	{
		std::string s("error loading texture");
		throw std::exception(s.c_str());
	}

	m_sprite_scrap[0].setTexture(m_texture_scrap);

	m_sprite_scrap[1].setTexture(m_texture_scrap);
	m_sprite_scrap[1].setOrigin(50, 50.5);
	m_sprite_scrap[1].setScale(0.5f, 0.5f);


}

Upgrade::~Upgrade()
{
	std::cout << "destroying upgrade menu" << std::endl;
}

void Upgrade::update(double t, Xbox360Controller &controller)
{

	if (!controller.Abutton() && !controller.Bbutton()) // button release check
	{
		button_released = true;
	}

	if (!m_status)
	{
		if (controller.Abutton() && button_released)// move to status select
		{
			m_status = true;
			button_released = false; // when button pressed 
		}

		if (controller.Bbutton() && button_released)// when player isn't in status back to mainmenu
		{
			backOut();
			button_released = false;
		}
	}
	else
	{
		if (controller.Abutton() && button_released && !warning)
		{
			if (scrap > 0)
			{
				switch (button_ID)
				{
				case 0:
					if (whiteCar_status[status_ID] < 3)
					{
						whiteCar_status[status_ID]++;
						scrap--;
					}
					break;
				case 1:
					if (redCar_status[status_ID] < 3)
					{
						redCar_status[status_ID]++;
						scrap--;
					}
					break;
				case 2:
					if (yellowCar_status[status_ID] < 3)
					{
						yellowCar_status[status_ID]++;
						scrap--;
					}
					break;
				case 3:
					if (greenCar_status[status_ID] < 3)
					{
						greenCar_status[status_ID]++;
						scrap--;
					}
				default:
					break;
				}
				button_released = false;
			}
			else
			{
				warning = true;
			}
		}

		if (controller.Bbutton() && button_released) // when player isn in status back to car select
		{
			status_ID = 0;
			m_status = false;
			button_released = false;
		}

		m_selecter.setPosition(m_textMessage[status_ID].getPosition().x - 10, m_textMessage[status_ID].getPosition().y - 10); // set seleter's positoin
		m_sprite_scrap[1].setPosition(m_textMessage[status_ID].getPosition().x + 25, m_textMessage[status_ID].getPosition().y + 75); // set seleter's positoin
		m_sprite_scrap[1].rotate(3);

		m_textMessage[11].setPosition(m_sprite_scrap[1].getPosition().x + 50, m_sprite_scrap[1].getPosition().y);
	}

	if (warning)
	{
		warning_time -= t;
		m_size.y -= 2; // decrease the high of the warning background

		if (warning_time <= 0)
		{
			warning_time = 1.0f;
			warning = false;
			m_size.y = 200;
		}
		warning_back.setSize(m_size);
		warning_back.setOrigin(m_size.x / 2, m_size.y / 2);
	}

	if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
	{
		if (!m_status)
		{
			if (button_ID < 3)
			{
				button_ID++;
			}
			else
			{
				button_ID = 0;
			}
		}
		else
		{
			if (status_ID < 2)
			{
				status_ID++;
			}
			else
			{
				status_ID = 0;
			}

		}
	}

	if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
	{

		if (!m_status)
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
		else
		{
			if (status_ID > 0)
			{
				status_ID--;
			}
			else
			{
				status_ID = 2;
			}
		}
	}
	// use up and down arrow to select car

	if (button_ID == 0)
	{
		if (m_Sprite[0].getPosition().x < 450)//any key accepted to change screen to credits
		{
			m_Sprite[0].move(10, 0);
		}
		m_Sprite[1].setPosition(325, 200);
		m_Sprite[2].setPosition(325, 400);
		m_Sprite[3].setPosition(325, 600);

		m_sprite_scrap[0].setPosition(0, 50);
		m_textMessage[10].setPosition(100, 60);
		m_textMessage[10].setString(intToString(scrap));

		whiteCar_values[0] = 100 + whiteCar_status[0] * 3;
		whiteCar_values[1] = 4.2 - whiteCar_status[1] * 0.4;
		whiteCar_values[2] = 50 + whiteCar_status[2] * 5;

		m_textMessage[4].setString(intToString(whiteCar_values[0]) + " kph");//set Max Speed
		m_textMessage[5].setString(intToString(whiteCar_values[1]) + " sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString(intToString(whiteCar_values[2]) + "%");//set Handling

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

		m_sprite_scrap[0].setPosition(0, 250);
		m_textMessage[10].setPosition(100, 260);
		m_textMessage[10].setString(intToString(scrap));

		reaCar_values[0] = 90 + redCar_status[0] * 6;
		reaCar_values[1] = 3.9 - redCar_status[1] * 0.35;
		reaCar_values[2] = 55 + redCar_status[2] * 4;

		m_textMessage[4].setString(intToString(reaCar_values[0]) + " kph");//need to be changed to a player editable varible
		m_textMessage[5].setString(intToString(reaCar_values[1]) + " sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString(intToString(reaCar_values[2]) + "%");//set Handling
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

		m_sprite_scrap[0].setPosition(0,450);
		m_textMessage[10].setPosition(100, 460);
		m_textMessage[10].setString(intToString(scrap));

		yellowCar_values[0] = 98 + yellowCar_status[0] * 4;
		yellowCar_values[1] = 4.5 - yellowCar_status[1] * 0.5;
		yellowCar_values[2] = 25 + yellowCar_status[2] * 10;

		m_textMessage[4].setString(intToString(yellowCar_values[0]) + " kph");
		m_textMessage[5].setString(intToString(yellowCar_values[1]) + " sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString(intToString(yellowCar_values[2]) + "%");//set Handling
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

		m_sprite_scrap[0].setPosition(0, 650);
		m_textMessage[10].setPosition(100, 660);
		m_textMessage[10].setString(intToString(scrap));

		greenCar_values[0] = 94 + greenCar_status[0] * 5;
		greenCar_values[1] = 4.0 - greenCar_status[1] * 0.4;
		greenCar_values[2] = 30 + greenCar_status[2] * 8;

		m_textMessage[4].setString(intToString(greenCar_values[0]) + " kph");
		m_textMessage[5].setString(intToString(greenCar_values[1]) + " sec  to Max Speed");//set Aceeleration
		m_textMessage[6].setString(intToString(greenCar_values[2]) + "%");//set Handling
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

	window.draw(m_sprite_scrap[0]);
	window.draw(m_textMessage[10]);

	for (int i = 0; i < 4; i++)
	{
		window.draw(m_Sprite[i]);
	}


	if (m_status)
	{
		window.draw(m_selecter); // status seleter
		window.draw(m_sprite_scrap[1]); // scrap image
		window.draw(m_textMessage[11]); // scrap player needs
	}

	switch (button_ID)
	{
	case 0: // draw white car's status
		drawStatusShape(window, whiteCar_status[0], whiteCar_status[1], whiteCar_status[2]);
		break;
	case 1: // draw red car's status
		drawStatusShape(window, redCar_status[0], redCar_status[1], redCar_status[2]);
		break;
	case 2: // draw yellow car's status
		drawStatusShape(window, yellowCar_status[0], yellowCar_status[1], yellowCar_status[2]);
		break;
	case 3: // draw green car's status
		drawStatusShape(window, greenCar_status[0], greenCar_status[1], greenCar_status[2]);
		break;
	default:
		break;
	}

<<<<<<< HEAD
//Sound_Difficulty
=======


//>>>>>>> Sound_Difficulty
>>>>>>> 050b7539f24fe526bf50edec9d04a79e4aa8cb92
	window.draw(m_textMessage[0]);
	window.draw(m_textMessage[1]);
	window.draw(m_textMessage[2]);//main menu draw
	window.draw(m_textMessage[3]);//setting draw 
	window.draw(m_textMessage[4]);
	window.draw(m_textMessage[5]);
	window.draw(m_textMessage[6]);

	if (warning)
	{
		window.draw(warning_back);
		window.draw(m_textMessage[12]);
	}

	//window.display();
}


void Upgrade::drawStatusShape(sf::RenderWindow &window, int maxSpeed, int acceleration, int handling)
{
	for (int i = 0; i < maxSpeed + 1; i++)
	{
		window.draw(Max_speed_shape[i]);
	}

	for (int i = 0; i < acceleration + 1; i++)
	{
		window.draw(Acceleration_shape[i]);
	}

	for (int i = 0; i < handling + 1; i++)
	{
		window.draw(Handling_shape[i]);
	}

	if (maxSpeed == 3)
	{
		window.draw(m_textMessage[7]);
	}
	if (acceleration == 3)
	{
		window.draw(m_textMessage[8]);
	}
	if (handling == 3)
	{
		window.draw(m_textMessage[9]);
	}

}

std::string Upgrade::intToString(float num) {
	char numString[256];
	sprintf_s(numString, "%.1f", num);
	return numString;
}
