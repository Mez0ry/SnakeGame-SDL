#ifndef SnakeGame_GAME_SCORE_HPP
#define SnakeGame_GAME_SCORE_HPP
#include "../FontManager/FontManager.hpp"
#include "../TextureManager/TextureManager.hpp"

#include "../Observer/Observer.hpp"
#include "../Food/Food.hpp"
#include "../Observer/Subject/Subject.hpp"
#include "../Entity/EntityNull.hpp"
#include <list>
#include <fstream>

class GameScore : public Observer, public Subject{
private:
  TextureManager m_BackTexture;
public:
  GameScore();
  ~GameScore();
  void OnCreate();
  void OnDestroy();
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
  FontManager m_FontManager;
  SDL_Color m_ScoreColor = {255, 255, 255, 255};
  int m_Score;
  std::string m_ScoreHistoryPath;
  const char* m_ScoreHistoryFileName = "score_history.cfg";
};
#endif //! SnakeGame_GAME_SCORE_HPP