#include "Subject.hpp"
Subject::Subject(){
    m_ObserversVec.reserve(MAX_OBSERVERS);
}

Subject::~Subject() {

}

void Subject::AddObserver(Observer *observer)
{
    if(m_ObserversVec.size() >= MAX_OBSERVERS){
        assert("Can't add observer, Error: Limit for adding observers reached");
        return;
    }

    auto it = std::find_if(m_ObserversVec.begin(), m_ObserversVec.end(), [&](auto i){
         return (std::addressof(i) == std::addressof(observer)); 
    });

    if (it != m_ObserversVec.end())
    {
        puts("Observer not added, Error: List already contains this observer");
        return;
    }

    m_ObserversVec.push_back(observer);
}

void Subject::RemoveObserver(Observer *observer) {
   m_ObserversVec.erase(std::remove_if(m_ObserversVec.begin(),m_ObserversVec.end(),[&](auto obj){ return (std::addressof(obj) == std::addressof(observer)); }));
}

void Subject::Notify(const Entity &entity, ObserverEvents event)
{
    for (std::vector<Observer*>::const_iterator it = m_ObserversVec.cbegin(); it != m_ObserversVec.cend(); ++it)
    {
        (*it)->onNotify(entity, event);
    }
}