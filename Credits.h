/// <summary>
/// i am conr i am code good for porjct
/// </summary>

#ifndef CREDITS
#define CREDITS
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include "Game.h"
#include <fstream>
class Game;

class Credits
{
public:
	Credits(Game& game, sf::Font font, sfe::Movie);
	~Credits();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void changeScreen();

private:

	bool endMovie = false;
	bool closeGame = false;
	float updateShader;//variables for shaders
	sf::Shader shader;
	sf::Texture shaderTxt;
	sf::Sprite shaderSprite;

	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Text m_credits;
	std::string textline;
	sf::Font m_impact;
	sf::Text m_textMessage;
	sfe::Movie m_movie;
	

};

#endif // !CREDITS
