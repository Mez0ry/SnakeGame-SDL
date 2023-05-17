#ifndef __SOUNDFACTORY_HPP__
#define __SOUNDFACTORY_HPP__
#include "Sound.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

struct SoundManagerModel {
  explicit SoundManagerModel(const std::string& sound_path, const std::string& sound_name) : sSoundPath(sound_path),sSoundName(sound_name) {}
  std::string sSoundName;
  std::string sSoundPath;
};

class SoundManager {
private:
  using MapType = std::unordered_map<std::string, std::shared_ptr<Sound>>;

public:
  SoundManager() = default;
  ~SoundManager() = default;

  void AddSound(const SoundManagerModel &sound) {
    if (SoundInMap(sound.sSoundName)) {
      return;
    }

    m_SoundMap.insert(std::make_pair(sound.sSoundName, std::make_shared<Sound>(sound.sSoundPath.c_str())));
  }

  void RemoveSound(const std::string &sound_name) {
    MapType::iterator it = m_SoundMap.find(sound_name);
    if (it != m_SoundMap.end()) {
      m_SoundMap.erase(it);
    }
  }

  [[nodiscard]] std::shared_ptr<Sound>& FindSound(const std::string &sound_name) {
    MapType::iterator it = m_SoundMap.find(sound_name);
    if (it != m_SoundMap.end()) {
      return it->second;
    }
    throw std::logic_error("Map not contain sound, with name: " + sound_name);
  }

  [[nodiscard]] std::shared_ptr<Sound>& operator[](const std::string &sound_name){
    return FindSound(sound_name);
  }
  
private:
  bool SoundInMap(const std::string &sound_name) {
    MapType::iterator it = m_SoundMap.find(sound_name);
    if (it != m_SoundMap.end()) {
      return true;
    }
    return false;
  }

private:
  MapType m_SoundMap;
};
#endif // __SOUNDFACTORY_HPP__