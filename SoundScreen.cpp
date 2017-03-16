#include "SoundScreen.h"

Sound::Sound(Game &game, sf::Font Font, sf::Font Font2) :
	m_game(&game),
	m_motor(Font),
	m_harlow(Font2)
{
	message[0].setFont(m_harlow);
	message[0].setString("Sound Settings");
	message[0].setPosition(350, 50);
	message[0].setCharacterSize(100);
	message[0].setColor(sf::Color::Red);

	message[1].setFont(m_motor);
	message[1].setString("Sound");
	message[1].setPosition(200, 200);
	message[1].setCharacterSize(50);
	message[1].setColor(sf::Color::Black);

	message[2].setFont(m_motor);
	message[2].setString("FX");
	message[2].setPosition(200, 400);
	message[2].setCharacterSize(50);
	message[2].setColor(sf::Color::Black);

	message[3].setFont(m_motor);
	message[3].setString("Volume");
	message[3].setPosition(200, 600);
	message[3].setCharacterSize(50);
	message[3].setColor(sf::Color::Black);

	if (!scrollBarTxt[0].loadFromFile("images/circlemover.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!scrollBarTxt[1].loadFromFile("images/bar.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!selectorTxt.loadFromFile("images/selector.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	scrollBarSprite[0].setTexture(scrollBarTxt[0]);
	scrollBarSprite[0].setPosition(250, 695);
	scrollBarSprite[1].setTexture(scrollBarTxt[1]);
	scrollBarSprite[1].setPosition(175, 700);

	for (int i = 0; i < 2; i++)
	{
		toggleButtons[i].setSize(sf::Vector2f(30.0f, 30.0f));
		toggleButtons[i].setFillColor(sf::Color::Green);
	}
	toggleButtons[0].setPosition(250, 300);
	toggleButtons[1].setPosition(250, 500);

	selectorSprite.setTexture(selectorTxt);
}

Sound::~Sound()
{
	std::cout << "destroying Sound Screen " << std::endl;
}

void Sound::Update(sf::Time time , Xbox360Controller &controller)
{
	
	if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
	{
		if (button_ID < 2)
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
		if (button_ID > 0)
		{
			button_ID--;
		}
		else
		{
			button_ID = 2;
		}
	}
	if (controller.m_currentState.B)
	{
		changeScreen();
	}

	if (button_ID == 0)
	{
		selectorSprite.setPosition(180, 300);
		if (controller.m_currentState.A && !controller.m_previousState.A && on==true)
		{
			on = false;
			off = true;
		}
		else if (controller.m_currentState.A && !controller.m_previousState.A && off == true)
		{
			on = true;
			off = false;
		}
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 1)
	{
		selectorSprite.setPosition(180, 500);
		if (controller.m_currentState.A && !controller.m_previousState.A && FXon == true)
		{
			FXon = false;
			FXoff = true;
		}
		else if (controller.m_currentState.A && !controller.m_previousState.A && FXoff == true)
		{
			FXon = true;
			FXoff = false;
		}
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 2)
	{
		selectorSprite.setPosition(150, 600);
		controller.m_previousState = controller.m_currentState;
	}

	if (button_ID == 2 && controller.m_currentState.DPadRight)
	{
		if (scrollBarSprite[0].getPosition().x <=350)
		{
			scrollBarSprite[0].move(7, 0);
		}
		if (soundVolume <= 100)
		{
			soundVolume += 4;
		}
		m_game->songs[0].setVolume(soundVolume);
		std::cout << "volume" << soundVolume << std::endl;

	}
	if (button_ID == 2 && controller.m_currentState.DPadLeft)
	{
		if (scrollBarSprite[0].getPosition().x >= 175)
		{
			scrollBarSprite[0].move(-7, 0);
		}
		if (soundVolume >= 0)
		{
			soundVolume -= 4;
		}
		m_game->songs[0].setVolume(soundVolume);
	}

	if (on == true)
	{
		toggleButtons[0].setFillColor(sf::Color::Green);
		m_game->songs[0].setVolume(soundVolume);
	
	}
	else if (off == true)
	{
		toggleButtons[0].setFillColor(sf::Color::Red);
		m_game->songs[0].setVolume(0);
	}
	if (FXon == true)
	{
		toggleButtons[1].setFillColor(sf::Color::Green);
		m_game->buttonsound.setVolume(soundVolume);

	}
	else if (FXoff == true)
	{
		toggleButtons[1].setFillColor(sf::Color::Red);
		m_game->buttonsound.setVolume(0);
	}
	
}

void Sound::changeScreen()
{
	m_game->SetGameState(GameState::option);
}

void Sound::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(225, 225, 225));
	for (int i = 0; i < 4; i++)
	{
		window.draw(message[i]);
	}
	window.draw(toggleButtons[0]);
	window.draw(toggleButtons[1]);
	for (int i = 1; i >=0 ; i--)
	{
		window.draw(scrollBarSprite[i]);
	}
	window.draw(selectorSprite);
}