#pragma once

#include <typeinfo>
#include <type_traits>

class Event;

template<class T>
class EventListener {
public:

    EventListener() {
        static_assert(std::is_base_of<Event, T>::value, "EventListener<T>: T must be a class derived from Event");
    }

    virtual ~EventListener() {}

    virtual void onEvent(T &) = 0;

};



