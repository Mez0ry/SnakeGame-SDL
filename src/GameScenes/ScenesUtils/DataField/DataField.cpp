#include "DataField.hpp"
DataField::DataField() : m_isActive(true)
{
    const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
    m_DataModel.game_number = -1;
    m_DataModel.score = -1;
    m_DataModel.minutes = -1;
    m_DataModel.seconds = -1;

    for (int i = 0; i < 4; i++)
    {
        m_DataModel.m_Text[i].LoadFont((CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "fonts" + symbol + "Comic_CAT.otf").c_str(), 20);
    }

    m_DataModel.m_Delimiter.LoadFont((CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "fonts" + symbol + "Comic_CAT.otf").c_str(), 20);
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

    int internal_data_position_x = m_DataFieldTexture.get_dstRect().x + 15;
    int internal_data_position_y = m_DataFieldTexture.get_dstRect().y;
    int space_between_internal_data = 115;

    for (int i = 0; i < 2; i++)
    {
        m_DataModel.m_Text[i].set_dstRect((internal_data_position_x + (i * space_between_internal_data)), (internal_data_position_y + (m_DataFieldTexture.get_srcRect().h / 2)) - 10, 20, 20);
    }

    space_between_internal_data += 23;

    m_DataModel.m_Text[2].set_dstRect((internal_data_position_x + (2 * space_between_internal_data)), (internal_data_position_y + (m_DataFieldTexture.get_srcRect().h / 2)) - 10, 20, 20);
    m_DataModel.m_Text[3].set_dstRect((m_DataModel.m_Text[2].get_dstRect().x + (2 * 20)), (internal_data_position_y + (m_DataFieldTexture.get_srcRect().h / 2)) - 10, 20, 20);
    m_DataModel.m_Delimiter.set_dstRect(((m_DataModel.m_Text[2].get_dstRect().x + (m_DataModel.m_Text[2].get_dstRect().w / 2)) + m_DataModel.m_Text[3].get_dstRect().x) / 2, (internal_data_position_y + (m_DataFieldTexture.get_srcRect().h / 2)) - 10, 10, 20);
}

void DataField::Render()
{
    m_DataFieldTexture.DestroyTexture();
    m_DataFieldTexture.ReloadTexture();
    m_DataFieldTexture.RenderTexture();

    int *pInnerDataField = (&m_DataModel.game_number);

    for (int i = 0; i < 4; i++, pInnerDataField++)
    {
        m_DataModel.m_Text[i].DestroySurfaceAndTexture();
        m_DataModel.m_Text[i].LoadSurfaceAndTexture(std::to_string(*pInnerDataField).c_str(), {100, 165, 204, 255});
        m_DataModel.m_Text[i].RenderCopy();
    }
    m_DataModel.m_Delimiter.DestroySurfaceAndTexture();
    m_DataModel.m_Delimiter.LoadSurfaceAndTexture(":", {100, 165, 204, 255});
    m_DataModel.m_Delimiter.RenderCopy();
}

void DataField::LoadTexture(const std::string &texture_path, ImageType type /*= ImageType::PNG*/)
{
    m_DataFieldTexture.LoadTexture(texture_path, type);
}

void DataField::set_Activity(bool activity_state)
{
    this->m_isActive = activity_state;
}
