#ifndef _VECTOR_HPP
#define _VECTOR_HPP
#include <algorithm>
#include <iostream>
#include <math.h>

struct Vec2 {
  int x, y;

  Vec2() = default;
  Vec2(int pos_x, int pos_y) : x(pos_x), y(pos_y) {}
  Vec2(const Vec2& other){(*this).x = other.x; (*this).y = other.y; }
  ~Vec2() = default;
  
  friend void swap(Vec2& lhs, Vec2& rhs){
    std::swap(lhs.x,rhs.x);
    std::swap(lhs.y,rhs.y);
  }
  /**
   * @brief used to get length/magnitude  of the vector
   * @return magnitude
  */
  double Magnitude() const {return std::sqrt(this->x * this->x + this->y * this->y);}

  /**
   * @brief used to get length/magnitude of the vector
   * @return length
  */
  double Length() const {return std::sqrt(DotProduct({this->x,this->y},{this->x,this->y}));}

  /**
   * @brief used to get distance
   * @return distance
  */
  static int Distance(const Vec2& lhs, const Vec2& rhs){
    Vec2 res{std::abs(lhs.x - rhs.x),std::abs(lhs.y - rhs.y)};
    return res.Length();
  }

  float GetMaxComponent() const{
    return std::max(x,y);
  }

  float GetMinComponent() const{
    return std::min(x,y);
  }

  float Angle(const Vec2& other) const
  {
    return std::acos(this->DotProduct((*this),other) / Magnitude() * other.Magnitude());
  }

  static float Angle(const Vec2& lhs,const Vec2& rhs){
    return std::acos(DotProduct(lhs,rhs) / lhs.Magnitude() * rhs.Magnitude());
  }

  /**
   * @brief normalize vector
   * @return unit vector on success otherwise empty vector
  */
  Vec2 Normalize() const{
    double magnitude = this->Magnitude();
    if(magnitude == 0) return {0,0};

    float inv_mag = 1.0f / magnitude;
    const Vec2 cpy = {(int)(x * inv_mag), (int)(y * inv_mag)};
    return cpy;
  }
  
  Vec2 PositivePerpendicular() const
  {
    return {-y, x};
  }

  Vec2 NegativePerpendicular() const
  {
    return {y, -x};
  }

  /**
   * @brief used to get dot product
   * @return dot product
  */
  static double DotProduct(const Vec2& lhs, const Vec2& rhs){
    return (lhs.x * rhs.x + lhs.y * rhs.y);
  }

  static Vec2 Lerp(const Vec2& lhs, const Vec2& rhs, float t)
  {
    t = std::clamp(t, 0.0f, 1.0f);
    return {(int)(lhs.x + (rhs.x - lhs.x) * t),(int)(lhs.y + (rhs.y - lhs.y) * t)};
  }
  
  /** Comparison operators*/
  Vec2 operator-(const Vec2& rhs) const{
    return {this->x - rhs.x, this->y - rhs.y};
  }

  Vec2 operator-(Vec2& rhs) const{
    return {this->x - rhs.x, this->y - rhs.y};
  }

  Vec2 operator+(const Vec2& rhs) const{
    return {this->x + rhs.x, this->y + rhs.y};
  }

  Vec2& operator+=(const Vec2& rhs){
    this->x += rhs.x;
    this->y += rhs.y;
    return *this; 
  }

  Vec2& operator-=(const Vec2& rhs){
    this->x -= rhs.x;
    this->y -= this->y - rhs.y;
    return *this; 
  }

  inline friend std::ostream& operator<< (std::ostream &out, const Vec2 &vec){
    out << "Vector(" << vec.x << "," << vec.y << ")";
    return out;
  }

  bool operator==(const Vec2 &rhs) const {
    return (this->x == rhs.x && this->y == rhs.y);
  }

  bool operator!=(const Vec2 &rhs) const {
    return !(this->x == rhs.x && this->y == rhs.y);
  }
  
  /** Assignment operators*/
  Vec2& operator=(Vec2 other){
    if (this == &other){//self assignment
      return (*this);
    }
    swap((*this),other);
    return (*this);
  }

  Vec2 operator+=(const float scalar)
  {
    this->x += scalar;
    this->y += scalar;
    return *this;
  }

  Vec2 operator-=(const float scalar)
  {
    this->x -= scalar;
    this->y -= scalar;
    return *this;
  }

  Vec2 operator*=(const float scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  Vec2 operator/=(const float scalar)
  {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
  }

  inline Vec2 operator+(const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp += (int)scalar;
  }

  inline Vec2 operator-( const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp -= (int)scalar;
  }

  inline Vec2 operator*(const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp *= (int)scalar;
  }

  inline Vec2 operator*(const Vec2& vec)
  {
    return {(*this).x * vec.x, (*this).y * vec.y};
  }

  inline Vec2 operator/(const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp /= scalar;
  }
};

/**@brief for compatability with stl unordered_map*/
template <>
struct std::hash<Vec2>
{
  std::size_t operator()(const Vec2& vec) const
  {
    return ((std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1)) >> 1);
  }
};

#endif //!_VECTOR_HPP