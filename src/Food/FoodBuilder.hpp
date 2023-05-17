#ifndef __FOOD_BUILDER_HPP__
#define __FOOD_BUILDER_HPP__
#include "Food.hpp"

class FoodBuilder {
private:

public:
  FoodBuilder() = default;
  ~FoodBuilder() = default;
  
  FoodBuilder& LoadTexture(const std::string& path){
    m_Food.GetTexture().LoadTexture(path);
    return (*this);
  }

  FoodBuilder& ShareSDLTexture(const Texture& texture){
    m_Food.GetTexture().ShareSDLTexture(texture);
    return (*this);
  }

  FoodBuilder& SetPos(const Vec2& pos){
    m_Food.SetPosition(pos);
    return (*this);
  }

  FoodBuilder& SetTextureSize(const TextureSize& size){
    m_Food.SetSize(size);
    return (*this);
  }
  
  
  FoodBuilder& SetSourceTexture(const Vec2& source_texture_pos,const TextureSize &size){
    m_Food.GetTexture().SetTextureSize<SourceRect>(size);
    m_Food.GetTexture().SetTexturePosition<SourceRect>(source_texture_pos);
    return (*this);
  }

 [[nodiscard]] Base::Ref<Food> build(){
    return std::make_shared<Food>(std::move(m_Food));
  }
  
private:
  Food m_Food;
};

#endif // __FOOD_BUILDER_HPP__