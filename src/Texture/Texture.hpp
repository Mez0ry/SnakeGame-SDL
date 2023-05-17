#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
#include "../CSDLContext/CSDLContext.hpp"

#include "../Vector.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "../Base.hpp"

struct TextureSize {
  TextureSize() = default;
  TextureSize(int width, int height) : w_(width), h_(height) {}
  ~TextureSize() = default;

  int GetWidth() const {return w_;}
  int GetHeight() const {return h_;}

  TextureSize& operator+=(const TextureSize& rhs)
  {            
    this->w_ += rhs.w_;
    this->h_ += rhs.h_;

    return *this; // return the result by reference
  }

  friend TextureSize operator+(TextureSize lhs,const TextureSize& rhs){
      return (lhs += rhs);
  }
  
private:
  int w_, h_;
};

struct SourceRect {};
struct DestRect {};

template<typename,typename = DestRect>
constexpr bool is_dst_rect_v;

template<typename T>
constexpr bool is_dst_rect_v<T, DestRect> = std::is_same<T, DestRect>::value;

template<typename,typename = SourceRect> 
constexpr bool is_src_rect_v;

template<typename T>
constexpr bool is_src_rect_v<T,SourceRect> = std::is_same<T,SourceRect>::value;

struct TextureDeleter {
  void operator()(SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
};

struct SDL_Texture;

class Texture {
private:
public:
  Texture() noexcept;
  Texture(const std::string& texture_path);
  ~Texture() noexcept;

  Texture(Texture&& other) noexcept{
    this->m_texture = std::move(other.m_texture);
    other.m_texture = nullptr;
    
    this->m_src = std::move(other.m_src);
    this->m_dst = std::move(other.m_dst);
  }

  Texture(const Texture& other){
    this->m_texture = other.m_texture;

    this->m_src = other.m_src;
    this->m_dst = other.m_dst;
  }
  
  Base::Ref<SDL_Texture> LoadTexture(const std::string &path);

  [[nodiscard]] static Base::Ref<SDL_Texture> CreateTextureFromSurface(SDL_Surface* surface);

  void ShareSDLTexture(const Texture& texture);
  void ShareSDLTexture(const Base::Ref<SDL_Texture>& texture);
  void Reset();
  
  /**
   * @return Returns the number of different shared_ptr instances (this included) managing inner SDL_Texture pointer
  */
  long TextureUseCount(){
    return m_texture.use_count();
  }

  template<typename T = DestRect>
  void SetRect(const Vec2& pos, const TextureSize& size){
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    SetTexturePosition<T>(pos);
    SetTextureSize<T>(size);
  }

  template<typename T = DestRect>
  const SDL_Rect& GetRect() const{
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>){
      return m_src;
    }else if(is_dst_rect_v<T>){
      return m_dst;
    }
  }

  template<typename T = DestRect>
  SDL_Rect& GetRect(){
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>){
      return m_src;
    }else if(is_dst_rect_v<T>){
      return m_dst;
    }
  }

  template <typename T = DestRect>
  void SetTextureSize(const TextureSize& size){
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>) {
      m_src.w = size.GetWidth();
      m_src.h = size.GetHeight();

    } else if constexpr (is_dst_rect_v<T>) {
      m_dst.w = size.GetWidth();
      m_dst.h = size.GetHeight();
    }
  }

  template <typename T = DestRect>
  void SetTexturePosition(const Vec2& pos){
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>) {
      m_src.x = pos.x;
      m_src.y = pos.y;

    } else if constexpr (is_dst_rect_v<T>) {
      m_dst.x = pos.x;
      m_dst.y = pos.y;
    }
  }

  template<typename T = DestRect>
  Vec2 GetTexturePosition() const{
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>) {
      return Vec2(m_src.x,m_src.y);
    } else if constexpr (is_dst_rect_v<T>) {
      return Vec2(m_dst.x,m_dst.y);
    }
  }

  template<typename T = DestRect>
  TextureSize GetTextureSize() const{
     static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>) {
      return TextureSize(m_src.w,m_src.h);
    } else if constexpr (is_dst_rect_v<T>) {
      return TextureSize(m_dst.w,m_dst.h);
    }
  }

    template<typename T = DestRect>
  Vec2 GetTexturePosition(){
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) && "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>) {
      return Vec2(m_src.x,m_src.y);
    } else if constexpr (is_dst_rect_v<T>) {
      return Vec2(m_dst.x,m_dst.y);
    }
  }

  template<typename T = DestRect>
  TextureSize GetTextureSize(){
    static_assert((is_src_rect_v<T>) || (is_dst_rect_v<T>) &&  "template argument is neither SourceRect nor DestRect ");
    if constexpr (is_src_rect_v<T>) {
      return TextureSize(m_src.w,m_src.h);
    } else if constexpr (is_dst_rect_v<T>) {
      return TextureSize(m_dst.w,m_dst.h);
    }
  }

  [[nodiscard]] SDL_Texture *GetTexture() { return m_texture.get(); }

  bool PointIsOnTexture(const Vec2 &point) const;

  void RenderTexture();

  static bool isColliding(const Texture& lhs, const Texture& rhs ){
    if(lhs.bottom_left().y <= rhs.top_left().y){
      return false;
    }

    if(lhs.top_left().y >= rhs.bottom_left().y){
      return false;
    }

    if(lhs.top_right().x <= rhs.top_left().x){ 
      return false;
    }

    if(lhs.top_left().x >= rhs.top_right().x ){ 
      return false;
    }
    return true;
  }
  
  /**
   * @return top_left of the texture
  */
  const Vec2 top_left() const {
    return GetTexturePosition();
  }

  /**
   * @return top_right of the texture
  */
  const Vec2 top_right() const{
    auto pos_cpy = GetTexturePosition();
    pos_cpy.x += GetTextureSize().GetWidth();
    return pos_cpy;
  }
  
  /**
   * @return bottom_left of the texture
  */
  const Vec2 bottom_left() const{
    auto pos_cpy = GetTexturePosition();
    pos_cpy.y += GetTextureSize().GetHeight();

    return pos_cpy;
  }

  /**
   * @return bottom_right of the texture
  */
  const Vec2 bottom_right() const{
    auto pos_cpy = GetTexturePosition();
    pos_cpy.x += GetTextureSize().GetWidth();
    pos_cpy.y += GetTextureSize().GetHeight();
    return pos_cpy;
  }

public:
  SDL_Texture* operator*()
  {
    return (m_texture.get());
  }

  SDL_Texture* operator*() const
  {
    return (m_texture.get());
  }
  
  Texture& operator=(const Texture& other)
  {
    if(this == &other){
      return (*this);
    }
    this->m_texture = other.m_texture;

    this->m_src = other.m_src;
    this->m_dst = other.m_dst;
    return *this;
  }

  Texture& operator=(Texture&& other) noexcept
  {
    if(this == &other){
      return (*this);
    }
    this->m_dst = std::move(other.m_dst);
    this->m_src = std::move(other.m_src);
    this->m_texture = std::move(other.m_texture);

    return *this;
  }

  explicit operator bool() const noexcept{
    return (m_texture != nullptr);
  }
private:
  SDL_Rect m_src, m_dst;
  Base::Ref<SDL_Texture> m_texture;
};

namespace PixelAccess{
  struct PixelInfo{
    PixelInfo() : pitch(0),pixels(nullptr){}
    int pitch;
    uint8_t* pixels;
  };
  
  inline void PutPixel(const Vec2& pos, PixelInfo& pixel_info, const TextureSize& size, SDL_Color color){
    uint8_t rgba[4] = {color.r,color.g,color.b,color.a};
    memcpy(&pixel_info.pixels[(pos.y * size.GetWidth() + pos.x) * sizeof(rgba)],rgba,sizeof(rgba));
  }
}

#endif //! __TEXTURE_HPP__