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
public:
    DataField();
    ~DataField();

    void Update();
    void Render();

    void LoadTexture(const std::string &texture_path, ImageType type = ImageType::PNG);

    DataModel &get_DataModel() { return m_DataModel; }
    TextureManager &get_Texture() { return m_DataFieldTexture; }

private:
    TextureManager m_DataFieldTexture;
    DataModel m_DataModel;
};
#endif //! SnakeGame_DATA_FIELD_HPP