#include "DataField.hpp"
DataField::DataField() : m_isActive(true)
{
    const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
    m_DataModel.total_game_number = -1;
    m_DataModel.score = -1;
    m_DataModel.time = -1;

    for (int i = 0; i < 3; i++)
    {
        m_DataModel.m_Text[i].LoadFont((CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "fonts" + symbol + "HACKED.ttf").c_str(), 20);
    }
}

DataField::~DataField()
{
}

void DataField::Update()
{
    if ((m_DataFieldTexture.get_dstRect().y - m_DataFieldTexture.get_srcRect().h) < m_range.top || (m_DataFieldTexture.get_dstRect().y + m_DataFieldTexture.get_srcRect().h) > m_range.bottom)
    {
        m_isActive = false;
    }
    else
    {
        m_isActive = true;
    }

    if (!m_isActive)
        return;

    m_DataModel.m_Text[0].LoadSurfaceAndTexture(std::to_string(m_DataModel.total_game_number).c_str(), {100, 165, 204, 255});
    m_DataModel.m_Text[1].LoadSurfaceAndTexture(std::to_string(m_DataModel.score).c_str(), {100, 165, 204, 255});
    m_DataModel.m_Text[2].LoadSurfaceAndTexture(std::to_string(m_DataModel.time).c_str(), {100, 165, 204, 255});

    int internal_data_position_x = m_DataFieldTexture.get_dstRect().x + 15;
    int internal_data_position_y = m_DataFieldTexture.get_dstRect().y;
    int space_between_internal_data = 115;
    for (int i = 0; i < 3; i++)
    {
        if (i == 2)
            space_between_internal_data += 23;
        m_DataModel.m_Text[i].set_dstRect((internal_data_position_x + (i * space_between_internal_data)), (internal_data_position_y + (m_DataFieldTexture.get_srcRect().h / 2)) - 10, 20, 20);
    }
}

void DataField::Render()
{
    m_DataFieldTexture.DestroyTexture();
    m_DataFieldTexture.ReloadTexture();
    m_DataFieldTexture.RenderTexture();
    int *pInnerDataField = (&m_DataModel.total_game_number);

    for (int i = 0; i < 3; i++, pInnerDataField++)
    {
        m_DataModel.m_Text[i].DestroySurfaceAndTexture();
        m_DataModel.m_Text[i].LoadSurfaceAndTexture(std::to_string(*pInnerDataField).c_str(), {100, 165, 204, 255});
        m_DataModel.m_Text[i].RenderCopy();
    }
}

void DataField::LoadTexture(const std::string &texture_path, ImageType type /*= ImageType::PNG*/)
{
    m_DataFieldTexture.LoadTexture(texture_path, type);
}

void DataField::set_Activity(bool activity_state)
{
    this->m_isActive = activity_state;
}
