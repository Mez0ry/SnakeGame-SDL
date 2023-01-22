set(SUBJECT_HEADERS Subject/Subject.hpp)
set(SUBJECT_SOURCES Subject/Subject.cpp)

set(OBSERVER_HEADERS Observer.hpp ObserverEvents.hpp)

add_library(Observer SHARED ${SUBJECT_HEADERS} ${SUBJECT_SOURCES} ${OBSERVER_HEADERS})