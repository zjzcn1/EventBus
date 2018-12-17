#pragma once

#include <typeindex>
#include <typeinfo>
#include <vector>
#include <stdexcept>

/**
 * \brief The base event class, all events inherit from this class
 */
class Event {
public:
    /**
     * \brief Default constructor
     *
     * @param typeIndex The type ID of the inherited class
     * @param sender The sender of the event
     */
    Event() {
    }

    /**
     * \brief Empty virtual destructor
     */
    virtual ~Event() {}

};

