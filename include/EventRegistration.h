#pragma once

#include <list>

class EventRegistration
{
public:
    typedef std::list<EventRegistration*> Registrations;
    /**
     * \brief Represents a registration object for a registered event listener
     *
     * This object is stored in a collection with other listeners for the event type.
     *
     * @param listener The event listener
     * @param registrations The listener collection for this event type
     * @param sender The registered sender object
     */
    EventRegistration(void * const listener, Registrations * const registrations) :
            listener(listener),
            registrations(registrations)
    { }


    /**
     * \brief Empty virtual destructor
     */
    ~EventRegistration() { }


    /**
     * \brief Gets the event listener for this registration
     *
     * @return The event listener
     */
    void * const getListener() {
        return listener;
    }


    /**
     * \brief Removes an event listener from the registration collection
     *
     * The event listener will no longer receive events for this event type
     */
    virtual void removeListener() {
        registrations->remove(this);
    }

private:
    void * const listener;
    Registrations* const registrations;

};

typedef std::list<EventRegistration*> Registrations;