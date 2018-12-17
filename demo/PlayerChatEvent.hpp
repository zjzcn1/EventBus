#pragma once

#include "../include/Event.h"

#include <string>
#include <iostream>
#include <memory>

class PlayerChatEvent : public Event {
public:
    PlayerChatEvent(std::string const &msg) :
            msg(msg) {
        std::cout << msg << std::endl;
    }

    virtual ~PlayerChatEvent() {}

    std::string const &getMessage() {
        return msg;
    }

private:
    std::string const msg;

};

