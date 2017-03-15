#include "Map.h"


/// <summary>
/// constructor
/// </summary>
/// <param name="game"></param>
Map::Map(Game& game) :
	m_game(&game),
	m_count(0),
	m_counter(0),
	m_posYrowOne(0),
	m_posYrowTwo(0),
	m_posYrowThree(0),
	m_posYrowFour(0)
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

	/*m_sprites[0].setTexture(m_textures[0]);
	m_sprites[1].setTexture(m_textures[1]);
	m_sprites[2].setTexture(m_textures[2]);
	m_sprites[3].setTexture(m_textures[3]);
	m_sprites[4].setTexture(m_textures[4]);
	m_sprites[5].setTexture(m_textures[5]);
	m_sprites[6].setTexture(m_textures[6]);
	m_sprites[7].setTexture(m_textures[7]);
	m_sprites[8].setTexture(m_textures[8]);
	m_sprites[9].setTexture(m_textures[9]);
	m_sprites[10].setTexture(m_textures[10]);
	m_sprites[11].setTexture(m_textures[11]);
	m_sprites[12].setTexture(m_textures[12]);
	m_sprites[13].setTexture(m_textures[13]);
	m_sprites[14].setTexture(m_textures[14]);
	m_sprites[15].setTexture(m_textures[15]);*/

	
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

	
	//sprites list for the outer ring
	m_outerSprites[0].setPosition(0,-392);
	m_outerSprites[1].setPosition(305, -392);
	m_outerSprites[2].setPosition(610, -392);
	m_outerSprites[3].setPosition(915, -392);
	m_outerSprites[4].setPosition(0, 1568);
	m_outerSprites[5].setPosition(305, 1568);
	m_outerSprites[6].setPosition(610, 1568);
	m_outerSprites[7].setPosition(915, 1568);
	m_outerSprites[8].setPosition(-305, 0);
	m_outerSprites[9].setPosition(-305, 392);
	m_outerSprites[10].setPosition(-305, 784);
	m_outerSprites[11].setPosition(-305, 1176);
	m_outerSprites[12].setPosition(1220, 0);
	m_outerSprites[13].setPosition(1220, 392);
	m_outerSprites[14].setPosition(1220, 784);
	m_outerSprites[15].setPosition(1220, 1176);


	////row 1
	//for (int iOne = 4; iOne < 8; iOne++)
	//{
	//	m_sprites[iOne].setPosition(m_posYrowTwo, 392);
	//	m_posYrowTwo + 305;
	//}

	////row 2
	//for (int iTwo = 8; iTwo < 12; iTwo++)
	//{
	//	m_sprites[iTwo].setPosition(m_posYrowThree, 784);
	//	m_posYrowThree + 305;
	//}

	////row 3
	//for (int iThree = 12; iThree < 16; iThree++)
	//{
	//	m_sprites[iThree].setPosition(m_posYrowFour, 1176);
	//	m_posYrowFour + 305;
	//}
}

/// <summary>
/// draw the map array of sprites to the screen
/// draw the outer ring to the screen
/// </summary>
/// <param name="window"></param>
void Map::render(sf::RenderWindow& window)
{	
	window.clear(sf::Color(255,197,104, 255));
	for (int index = 0; index < 16; index++)
	{
		window.draw(m_sprites[index]);
	}
}