#pragma once
<<<<<<< HEAD
#define Level_Loader
#ifdef Level_Loader
=======
#ifndef Level_Loader
#define Level_Loader
>>>>>>> Ai_Car

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include "ResourcePath.hpp"

struct NodeData
{
	std::string m_type;
	sf::Vector2f m_position;
	double m_rotation;
};


struct LevelData
{
	std::vector<NodeData> m_node;
};

class LevelLoader
{
public:

	LevelLoader();

	static bool load(int nr, LevelData& level);
};

<<<<<<< HEAD
#endif // !Level_Loader
=======
#endif
>>>>>>> Ai_Car
