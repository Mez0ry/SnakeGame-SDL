#ifndef __OBJECT_POOL_HPP_
#define __OBJECT_POOL_HPP_
#include <vector>
#include <functional>

template <typename _Type>
struct ResourceInfo{
  _Type resource;
  int index = 0;
};

template <typename _Type> 
class ObjectPool {
public:
  ObjectPool() {
    m_InUse.resize(8,0);
    m_Objects.reserve(8);

    Allocate(8);
  }

  ~ObjectPool() {
    for (auto& obj : m_Objects) {
      delete obj.resource;
    }
    m_Objects.clear();
  }
  
  void ForEach(const std::function<void(_Type* object)>& cb){
    for(auto& info : m_Objects){
        cb(info.resource);
    }
  }

  void ForEachNotInUse(const std::function<void(_Type* object)>& cb){
    for(auto& info : m_Objects){
        if(!m_InUse[info.index]){
            cb(info.resource);  
        }
    }
  }

  [[nodiscard]] ResourceInfo<_Type*>& GetResource() {
    for(auto i = 0;i<m_Objects.size();i++){
      if(not m_InUse[i]){
        m_InUse[i] = true;
        return m_Objects[i];
      }
    }
    Allocate();
    m_InUse[m_Objects.back().index] = true;
    return m_Objects.back();
  }
 
  void ReturnResource(ResourceInfo<_Type*>& resource_info){
    m_InUse[resource_info.index] = false;
  }

private:

  void Allocate(size_t size = 1){
    for(auto i = 0;i < size;i++){
      ResourceInfo<_Type*> info;

      info.resource = new _Type();
      info.index = m_Objects.size();

      m_InUse.push_back(false);
      m_Objects.push_back(info);
    }
  }

private:
  std::vector<ResourceInfo<_Type*>> m_Objects;
  std::vector<bool> m_InUse;
};

#endif //!__OBJECT_POOL_HPP_