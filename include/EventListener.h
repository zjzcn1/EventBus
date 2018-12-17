#pragma once

#include <typeinfo>
#include <type_traits>
#include <memory>

// Forward declare the Event class
class Event;

/**
 * \brief Base class of all classes that listen for events
 *
 * For a class to be an event listener, it needs to inherit from EventListener
 * with the specific event type as the template parameter. A class can inherit from
 * multiple EventListener base classes each using a different template parameter.
 */
template<class T>
class EventListener {
public:

    /**
     * \brief Default constructor that enforces the template type
     */
    EventListener() {
        // An error here indicates you're trying to implement EventListener with a type that is not derived from Event
        static_assert(std::is_base_of<Event, T>::value, "EventListener<T>: T must be a class derived from Event");
    }

    /**
     * \brief Empty virtual destructor
     */
    virtual ~EventListener() {}


    /**
     * \brief Pure virtual method for implementing the body of the listener
     *
     * @param The event instance
     */
    virtual void onEvent(T &) = 0;


    /**
     * \brief Dispatches a generic event to the appropriate listener method
     *
     * This method is called by the EventBus and dispatches to the correct method by
     * dynamic casting the event parameter to the template type for this handler.
     *
     * @param e The event to dispatch
     */
    void dispatch(Event &e) {
        onEvent(dynamic_cast<T &>(e));
    }

};


