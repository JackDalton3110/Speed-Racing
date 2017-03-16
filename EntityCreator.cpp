#include "EntityCreator.h"

void NodeCreator::create(entityx::Entity& entity)
{
	auto volume = Volume();
	volume.m_box = CollisionBox(33, 23);

	entity.assign<Volume>(volume);
	entity.assign<Display>(sf::IntRect(85, 133, 13, 13));
	entity.assign<Position>(m_position, m_size);
	entity.assign<Node>();
}
