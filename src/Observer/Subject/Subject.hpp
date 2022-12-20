#ifndef SnakeGame_OBSERVER_SUBJECT_HPP
#define SnakeGame_OBSERVER_SUBJECT_HPP
#include <vector>
#include "../Observer.hpp"
#include <stdio.h>
#include <algorithm>
#include "cassert"
class Subject{
    public:
    Subject();
    ~Subject();

    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);

    void Notify(const Entity& entity, ObserverEvents event);
    private:
    std::vector<Observer*> m_ObserversVec;
    enum internal_sizes : unsigned int{
        MAX_OBSERVERS = 10
    };
};
#endif //!SnakeGame_OBSERVER_SUBJECT_HPP