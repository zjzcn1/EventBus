#pragma once

#include "EventListener.h"
#include "Event.h"

#include <list>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>


class EventBus {
public:
    EventBus() {}

    virtual ~EventBus() {}

    static EventBus *const getInstance() {
        if (instance == nullptr) {
            instance = new EventBus();
        }
        return instance;
    }

    template<class T>
    static void addListener(EventListener<T> &listener) {
        EventBus *instance = getInstance();

        std::list<void *> *listenersForEvent = instance->listeners[typeid(T)];
        if (listenersForEvent == nullptr) {
            listenersForEvent = new std::list<void *>();
            instance->listeners[typeid(T)] = listenersForEvent;
        }

        listenersForEvent->push_back(static_cast<void *>(&listener));
    }

    template<class T>
    static void removeListener(EventListener<T> &listener) {
        EventBus *instance = getInstance();

        std::list<void *> *listenersForEvent = instance->listeners[typeid(T)];
        if (listenersForEvent == nullptr) {
            return;
        }

        listenersForEvent->remove(static_cast<void *>(&listener));
    }

    static void fireEvent(Event &e) {
        EventBus *instance = getInstance();

        std::list<void*> *listenersForEvent = instance->listeners[typeid(e)];
        if (listenersForEvent == nullptr) {
            return;
        }

        for (auto listener : *listenersForEvent) {
            static_cast<EventListener<Event> *>(listener)->onEvent(e);
        }
    }


private:
    static EventBus *instance;

    std::unordered_map<std::type_index, std::list<void*>*> listeners;

};

