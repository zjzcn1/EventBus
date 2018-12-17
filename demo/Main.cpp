
#include "../include/EventListener.h"
#include "../include/EventBus.h"

#include "PlayerChatEvent.hpp"

#include <string>
#include <iostream>

class PlayerListener : public EventListener<PlayerChatEvent>
{
public:
	PlayerListener() { }

	virtual ~PlayerListener() { }

	virtual void onEvent(PlayerChatEvent & e) override {
		std::cout<<"The msg:" << e.getMessage()<<std::endl;
	}

};



/**
 * \brief Demo class showing off some functionality of the EventBus
 */
class EventBusDemo
{
public:
	EventBusDemo() {
		playerChatReg = nullptr;
	}

	virtual ~EventBusDemo() { }


	void start() {

		PlayerListener playerListener;

		playerChatReg = EventBus::addListener<PlayerChatEvent>(playerListener);

		PlayerChatEvent chat1("Hello I am Player 1!");
		EventBus::fireEvent(chat1);

		PlayerChatEvent chat2("Hello I am Player 2!");
		EventBus::fireEvent(chat2);


		// The HandlerRegistration object can be used to unregister the event listener
		playerChatReg->removeListener();


		// If a chat event is fired again, it will not be serviced since the handler has been unregistered
		PlayerChatEvent chat3("This chat message will not be serviced");
		EventBus::fireEvent(chat3);

		delete playerChatReg;
	}

private:
	EventRegistration* playerChatReg;

};


int main()
{
	printf("* * * EventBus Demo Program * * * \n");

	try
	{
		EventBusDemo demo;
		demo.start();
	}
	catch (std::runtime_error & e)
	{
		printf("Runtime exception: %s\n", e.what());
	}
}


