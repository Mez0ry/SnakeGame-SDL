#ifndef SnakeGame_GAME_SCORE_HPP
#define SnakeGame_GAME_SCORE_HPP
#include "../GUI/Text/Text.hpp"
#include "../Texture/Texture.hpp"

#include "../Observer/Observer.hpp"
#include "../Food/Food.hpp"
#include "../Observer/Subject/Subject.hpp"
#include "../Entity/EntityNull.hpp"
#include <list>
#include <fstream>
#include "../Serializer/Serializer.hpp"

class GameScore : public Observer, public Subject{
public:
  GameScore();
  ~GameScore();
  void OnCreate();
  void OnDestroy();
  void OnResize();

  void onNotify(const Entity& entity, ObserverEvents event) override;

  void Update();
  void Render();

  void Subtract(int num);
  void Add(int num);
public:
  constexpr GameScore &operator+(int rhs) {
    this->m_Score += rhs;
    return (*this);
  }
  constexpr GameScore &operator-(int rhs) {
    this->m_Score -= rhs;
    return (*this);
  }
  GameScore &operator+=(int rhs) {
    this->m_Score += rhs;
    return (*this);
  }
  GameScore &operator-=(int rhs) {
    this->m_Score -= rhs;
    return (*this);
  }

private:
  /** @brief contains score for every game client played*/
  std::list<int> m_GamesScore;
  Text m_ScoreText;
  Texture m_ScoreBarTexture;
  
  SDL_Color m_ScoreColor = {255, 255, 255, 255};
  int m_Score;
};
#endif //! SnakeGame_GAME_SCORE_HPP