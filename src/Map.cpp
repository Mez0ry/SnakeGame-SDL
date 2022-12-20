#include "Map.hpp"

Map::Map() : m_Map(nullptr)
{
	m_Map = new SquareType *[CAppSettings::instance().get_MapHeight()];
	for (short int write_index = 0; write_index < CAppSettings::instance().get_MapHeight(); write_index++)
	{
		m_Map[write_index] = new SquareType[CAppSettings::instance().get_MapWidth()];
	}

	m_MapTexture.set_srcRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);
	m_MapTexture.set_dstRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);

	const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
	std::string map_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "map" + symbol + "map_texture.png";
	m_MapTexture.LoadTexture(map_texture_path);
}

Map::~Map()
{
	for (short int delete_index = 0; delete_index < CAppSettings::instance().get_MapHeight(); delete_index++)
	{
		delete[] m_Map[delete_index];
	}
	delete m_Map;
}

void Map::OnCreate()
{
	for (short int row_index = 0; row_index < CAppSettings::instance().get_MapHeight(); ++row_index)
	{
		for (short int col_index = 0; col_index < CAppSettings::instance().get_MapWidth(); ++col_index)
		{
			m_Map[row_index][col_index] = SquareType::BACKGROUND;
		}
	}
}

void Map::Render()
{
	SquareType square_type = SquareType::UNKNOWN;
	
	#pragma omp parallel for collapse(row_index)

	for (short int row_index = 0; row_index < CAppSettings::instance().get_MapHeight(); row_index++)
	{
		for (short int col_index = 0; col_index < CAppSettings::instance().get_MapWidth(); col_index++)
		{
			square_type = m_Map[row_index][col_index];
			switch (square_type)
			{
			case static_cast<SquareType>(SquareType::BACKGROUND):
			{
				m_MapTexture.set_dstRect(MapUtils::CorrectWidthPosOnTheMap(col_index), MapUtils::CorrectHeightPosOnTheMap(row_index), TextureConstants::TextureWidth, TextureConstants::TextureHeight);
				m_MapTexture.RenderTexture();
				break;
			}
			}
		}
	}
}
