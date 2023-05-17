#include "Map.hpp"

Vec2 Map::m_MapTopLeft;

Map::Map() : m_Map(nullptr)
{
	m_MapSize = {CAppSettings::instance().get_MapWidth(),CAppSettings::instance().get_MapHeight()};

	m_Map = new uint8_t *[m_MapSize.y];
	for (short int write_index = 0; write_index < m_MapSize.y; write_index++)
	{
		m_Map[write_index] = new uint8_t[m_MapSize.x];
	}

	auto dst_texture_size = TextureSize(32,32);
	auto src_texture_size(TextureSize(40,40));

	std::string src_folder = CAppSettings::instance().get_SourceFolder();

	std::string m_corner_paths[4] = {{(src_folder + CAppSettings::GetCorrectedPath("/assets/map/map_texture_tl.png"))},
									{(src_folder + CAppSettings::GetCorrectedPath("/assets/map/map_texture_tr.png"))},
									{src_folder + CAppSettings::GetCorrectedPath("/assets/map/map_texture_br.png")},
									{src_folder + CAppSettings::GetCorrectedPath("/assets/map/map_texture_bl.png")}};

	int path_index = 0;
	for(auto& rounded_corner : m_RoundedCorners){
		rounded_corner.SetTextureSize<SourceRect>(src_texture_size);
		rounded_corner.SetTextureSize(dst_texture_size);

		rounded_corner.SetTexturePosition<SourceRect>({0,0});
		rounded_corner.SetTexturePosition({0,0});
		rounded_corner.LoadTexture(m_corner_paths[path_index++]);
	}
	
	m_MapTexture.SetTextureSize<SourceRect>(src_texture_size);
	m_MapTexture.SetTextureSize(dst_texture_size);

    m_MapTexture.SetTexturePosition<SourceRect>({0,0});
	m_MapTexture.SetTexturePosition({0,0});

	std::string map_texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/map/map_texture.png");
	m_MapTexture.LoadTexture(map_texture_path);
}

Map::~Map()
{
	for (short int delete_index = 0; delete_index < m_MapSize.y; delete_index++)
	{
		delete[] m_Map[delete_index];
	}
	delete m_Map;
}

void Map::OnCreate()
{
	 
}

void Map::Render()
{
	#pragma omp parallel for collapse(row_index)

	/** key: corner_pos, value: corner_texture_index*/
	std::unordered_map<Vec2,int> corner_offsets = {{Vec2(0,0),0}, // top_left
												   {Vec2(m_MapSize.x - 1, 0),1}, // top_right
												   {Vec2(m_MapSize.x - 1,m_MapSize.y - 1),2}, // bottom_right
												   {Vec2(0,m_MapSize.y - 1),3}}; // bottom_left
	
	for (short int row_index = 0; row_index < CAppSettings::instance().get_MapHeight(); row_index++)
	{
		for (short int col_index = 0; col_index < CAppSettings::instance().get_MapWidth(); col_index++)
		{	
			Vec2 new_pos;
			new_pos.x = m_MapTopLeft.x + col_index * m_MapTexture.GetTextureSize().GetWidth();
			new_pos.y = m_MapTopLeft.y + row_index * m_MapTexture.GetTextureSize().GetHeight();
			
			auto it = corner_offsets.find({col_index,row_index});

			if(it != corner_offsets.end()){
				m_RoundedCorners[it->second].SetTexturePosition(new_pos);
				m_RoundedCorners[it->second].RenderTexture();
			}
			else{
				m_MapTexture.SetTexturePosition(new_pos);
				m_MapTexture.RenderTexture();
			}
		}
	}
}
