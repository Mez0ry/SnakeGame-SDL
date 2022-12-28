#ifndef SnakeGame_DATA_FIELD_HPP
#define SnakeGame_DATA_FIELD_HPP
#include "../../../TextureManager/TextureManager.hpp"
#include "../../../FontManager/FontManager.hpp"

typedef struct DataModel
{
    int game_number;
    int score;
    int minutes;
    int seconds;
    FontManager m_Text[4];
    FontManager m_Delimiter;
};

class DataField
{
    struct Range
    {
        int top, bottom;
    } m_range;

public:
    DataField();
    ~DataField();
    void OnCreate(const std::string &texture_path, ImageType = ImageType::PNG);

    void Update();
    void Render();

    void LoadTexture(const std::string &texture_path, ImageType type = ImageType::PNG);

    void set_Activity(bool activity_state);
    bool isActive() const { return m_isActive; }
    DataModel &get_DataModel() { return m_DataModel; }
    TextureManager &get_Texture() { return m_DataFieldTexture; }
    Range &get_Range() { return m_range; }

private:
    bool m_isActive = true;
    TextureManager m_DataFieldTexture;
    DataModel m_DataModel;
};
#endif //! SnakeGame_DATA_FIELD_HPP