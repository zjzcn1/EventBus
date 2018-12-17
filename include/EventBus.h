#pragma once

#include "EventListener.h"
#include "Event.h"
#include "EventRegistration.h"

#include <list>
#include <typeinfo>
#include <unordered_map>


/**
 * \brief An Event system that allows decoupling of code through synchronous events
 *
 */
class EventBus {
public:
    /**
     * \brief Default empty constructor
     */
    EventBus() {}


    /**
     * \brief Empty virtual destructor
     */
    virtual ~EventBus() {}


    /**
     * \brief Returns the EventBus singleton instance
     *
     * Creates a new instance of the EventBus if hasn't already been created
     *
     * @return The singleton instance
     */
    static EventBus *const getInstance() {
        if (instance == nullptr) {
            instance = new EventBus();
        }
        return instance;
    }

    /**
     * \brief Registers a new event listener to the EventBus with no source specified
     *
     * @param listener The event listener class
     * @return An EventRegistration pointer which can be used to unregister the event listener
     */
    template<class T>
    static EventRegistration* addListener(EventListener<T> &listener) {
        EventBus *instance = getInstance();

        // Fetch the list of event pairs unique to this event type
        Registrations* registrations = instance->listeners[typeid(T)];

        if (registrations == nullptr) {
            registrations = new Registrations();
            instance->listeners[typeid(T)] = registrations;
        }

        // Create a new EventPair instance for this registration.
        // This will group the handler, sender, and registration object into the same class
        EventRegistration* registration = new EventRegistration(static_cast<void*>(&listener), registrations);

        // Add the registration object to the collection
        registrations->push_back(registration);

        return registration;
    }


    /**
     * \brief Fires an event
     *
     * @param e The event to fire
     */
    static void fireEvent(Event &e) {
        EventBus *instance = getInstance();


        Registrations* registrations = instance->listeners[typeid(e)];
        if (registrations == nullptr) {
            return;
        }

        for (auto & reg : *registrations) {
            static_cast<EventListener<Event>*>(reg->getListener())->dispatch(e);
        }
    }


private:
    // Singleton class instance
    static EventBus *instance;

    std::unordered_map <std::type_index, std::list<EventRegistration*>*> listeners;

};

