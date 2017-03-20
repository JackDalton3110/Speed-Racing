#pragma once

//#include "entityx/Entity.h"
//#include "ICreatable.h"
//#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Node.h"

class NodeCreator : public ICreatable
{
public:
	NodeCreator(std::string type,
		sf::Vector2f position,
		int size);
	
	void create(entityx::Entity& entity);

private:
	std::string m_type;
	sf::Vector2f m_position;
	int m_size;
};

