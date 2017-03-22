#pragma once
#include <SFML\Graphics.hpp>
<<<<<<< HEAD
#include "BTMath.h" 
#include "Physics.h"
#include "Thor/Vectors.hpp"
=======
#include "Physics.h"
#include "BTMath.h"
#include <Thor/Vectors.hpp>
#include "LevelLoader.h"
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256

class NPCplayer
{
public:
<<<<<<< HEAD
	NPCplayer(std::vector<sf::CircleShape> &Node);
=======
	NPCplayer(std::vector<sf::CircleShape> & Node);
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256
	~NPCplayer();
	void update(double t, int car_id);
	void render(sf::RenderWindow &window);
	sf::Vector2f follow();

	sf::FloatRect getRect();
	sf::Vector2f m_motion;
<<<<<<< HEAD
	sf::Vector2f follow();
=======
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256

private:
	Physics physics;
	sf::Vector2f m_velocity;
	

	float m_acceleration;
	double m_degree;

	int m_dirction;
	float timer;

	int m_car_id;
	int currentNode = 0;
<<<<<<< HEAD
	const float MAX_FORCE = 6.0f;
	const float MAX_SEE_AHEAD=50.0f;
	float MAX_SPEED = 4.0F;

	sf::Vector2f m_steering;
=======
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::Vector2f m_postion;

	float located_time;
	sf::Vector2f location_record;

<<<<<<< HEAD
	std::vector<sf::CircleShape> m_NodeCircle;
=======
	std::vector<sf::CircleShape> & m_NodeCircle;
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256
};