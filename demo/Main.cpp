
#include "../include/EventListener.h"
#include "../include/EventBus.h"

#include <string>
#include <iostream>


class PlayerChatEvent : public Event {
public:
    PlayerChatEvent(std::string const &msg) :
            msg(msg) {
    }

    virtual ~PlayerChatEvent() {}

    std::string const &getMessage() {
        return msg;
    }

private:
    std::string const msg;

};

class PlayerListener : public EventListener<PlayerChatEvent> {
public:
    PlayerListener() {}

    virtual ~PlayerListener() {}

    virtual void onEvent(PlayerChatEvent &e) override {
        std::cout << "The msg:" << e.getMessage() << std::endl;
    }

};


int main() {
    printf("* * * EventBus Demo Program * * * \n");

    try {
        PlayerListener playerListener;

        EventBus::addListener<PlayerChatEvent>(playerListener);

        PlayerChatEvent chat1("Hello I am Player 1!");
        EventBus::fireEvent(chat1);

        PlayerChatEvent chat2("Hello I am Player 2!");
        EventBus::fireEvent(chat2);


        // The HandlerRegistration object can be used to unregister the event listener
        EventBus::removeListener(playerListener);

        // If a chat event is fired again, it will not be serviced since the handler has been unregistered
        PlayerChatEvent chat3("This chat message will not be serviced");
        EventBus::fireEvent(chat3);

        EventBus::addListener<PlayerChatEvent>(playerListener);

        // If a chat event is fired again, it will not be serviced since the handler has been unregistered
        PlayerChatEvent chat4("Hello I am Player 4!");
        EventBus::fireEvent(chat4);
    }
    catch (std::runtime_error &e) {
        printf("Runtime exception: %s\n", e.what());
    }
}


