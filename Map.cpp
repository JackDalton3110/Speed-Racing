#include "Map.h"


/// <summary>
/// constructor
/// </summary>
/// <param name="game"></param>
Map::Map(Game& game, Player & player) :
	m_game(&game),
	m_count(0),
	m_counter(0),
	m_player(player)
{

	// Loading in all the textures to the project
	m_textures[0].loadFromFile("images/slice_0_0.png");
	m_textures[1].loadFromFile("images/slice_0_1.png");
	m_textures[2].loadFromFile("images/slice_0_2.png");
	m_textures[3].loadFromFile("images/slice_0_3.png");
	m_textures[4].loadFromFile("images/slice_1_0.png");
	m_textures[5].loadFromFile("images/slice_1_1.png");
	m_textures[6].loadFromFile("images/slice_1_2.png");
	m_textures[7].loadFromFile("images/slice_1_3.png");
	m_textures[8].loadFromFile("images/slice_2_0.png");
	m_textures[9].loadFromFile("images/slice_2_1.png");
	m_textures[10].loadFromFile("images/slice_2_2.png");
	m_textures[11].loadFromFile("images/slice_2_3.png");
	m_textures[12].loadFromFile("images/slice_3_0.png");
	m_textures[13].loadFromFile("images/slice_3_1.png");
	m_textures[14].loadFromFile("images/slice_3_2.png");
	m_textures[15].loadFromFile("images/slice_3_3.png");
	


	/// <summary>
	/// For loops to add the array of textures to the 
	/// array of sprites.
	/// </summary>
	/// <param name="game"></param>
	for (int i = 0; i < 16; i++)
	{
		m_sprites[i].setTexture(m_textures[i]);
	}
	
	for (int i = 0; i < 16; i++)
	{
		m_outerSprites[i].setTexture(m_textures[16]);
	}

}

/// <summary>
/// destructor
/// </summary>
Map::~Map()
{
}

void Map::update()
{
	/// <summary>
	/// Setting the sprite positions
	/// the correct distance apart.
	/// Setting them in the correct tile positions
	/// </summary>
	/// <param name="deltaTime"></param>
	

	// sprites list for the track
	m_sprites[0].setPosition(0, 0);
	m_sprites[1].setPosition(305, 0);
	m_sprites[2].setPosition(610, 0);
	m_sprites[3].setPosition(915, 0);
	m_sprites[4].setPosition(0, 392);
	m_sprites[5].setPosition(305, 392);
	m_sprites[6].setPosition(610, 392);
	m_sprites[7].setPosition(915, 392);
	m_sprites[8].setPosition(0, 784);
	m_sprites[9].setPosition(305, 784);
	m_sprites[10].setPosition(610, 784);
	m_sprites[11].setPosition(915, 784);
	m_sprites[12].setPosition(0, 1176);
	m_sprites[13].setPosition(305, 1176);
	m_sprites[14].setPosition(610, 1176);
	m_sprites[15].setPosition(915, 1176);

	
	collision();
}

/// <summary>
/// getting pixel collision for offroad driving
/// </summary>
void Map::collision()
{
	bool offCircuit = false;
	for (int index = 0; index < 16; index++)
	{
		m_image = m_textures[index].copyToImage();
		m_findTile.x = m_player.m_postion.x - m_sprites[index].getPosition().x;
		m_findTile.y = m_player.m_postion.y - m_sprites[index].getPosition().y;
		

		if (m_findTile.x > 0 && m_findTile.y > 0)
		{
			
			if (m_findTile.x < 305 && m_findTile.y < 392)
			{
				//if (m_image.getPixel(0,0).b >= 106)	
				auto pixelColor = m_image.getPixel(m_findTile.x, m_findTile.y).b;

				//std::cout << m_player.getSpritePosition().x << " " << m_player.getSpritePosition().y << std::endl;

				if (m_image.getPixel(m_findTile.x , m_findTile.y).b <= 106)
				{
					//std::cout << "collision4" << std::endl;
					offCircuit = true;
					break;
					
				}
			}
		}

	}

	if (offCircuit)
	{
		m_player.highFriction();
	}
	else
	{
		m_player.normalFriction();
	}
	/*for (int i = 0; i < m_image.getSize().x; i++)
	{
		for (int j = 0; j < m_image.getSize().y; i++)
		{
			if (m_image.getPixel(i, j) == sf::Color(255, 204, 104, 255))
			{
				break;
			}
		}
	}*/
}

/// <summary>
/// draw the map array of sprites to the screen
/// clears to the same desert colour
/// </summary>
/// <param name="window"></param>
void Map::render(sf::RenderWindow& window)
{
	window.clear(sf::Color(255, 204, 104, 255));
	//window.clear(sf::Color::Black);

	//Culling
	for (int index = 0; index < 16; index++)
	{

		if (m_sprites[index].getPosition().x >= m_player.m_postion.x - (m_player.view.getSize().x + 50) && // window.getViewport.width &&
			m_sprites[index].getPosition().x <= m_player.m_postion.x + (m_player.view.getSize().x + 50) &&
			m_sprites[index].getPosition().y >= m_player.m_postion.y - (m_player.view.getSize().y + 200) &&
			m_sprites[index].getPosition().y <= m_player.m_postion.y + m_player.view.getSize().y + 200)
		{
			window.draw(m_sprites[index]);
		}

	}
}