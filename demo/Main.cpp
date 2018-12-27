#include <utility>

#include <utility>


#include "../src/EventBus.h"
#include "../src/ThreadPool.h"

#include <string>
#include <iostream>

using namespace eventbus;

struct ChatMsg {
    explicit ChatMsg(std::string m) {
        msg = std::move(m);
    }
    std::string msg;

    typedef std::shared_ptr<ChatMsg const> ConstPtr;
};



void onEvent(ChatMsg::ConstPtr e) {
    std::cout << "The msg:" << e->msg << std::endl;
}

int test(int a) {
    return a+2;
}

int main() {

//    ThreadPool pool(4);
//
//    auto result1 = pool.execute([](int answer) { return answer + 1 ; }, 42);
//    std::cout << result1.get() << std::endl;
//
//    auto result = pool.execute(test, 42);
//    std::cout << result.get() << std::endl;
//
//    EventBus::subscribe<ChatMsg>([](ChatMsg &e) {
//        std::cout<<e.msg << std::endl;;
//    });

    EventBus::subscribe<ChatMsg>(onEvent);

//    ChatMsg chat1("Hello I am Player 1!");
//    EventBus::publish<ChatMsg>(chat1);

    ChatMsg::ConstPtr chat2 = ChatMsg::ConstPtr(new ChatMsg("Hello I am Player 2!"));
    EventBus::publish<ChatMsg>(chat2);
//
//    std::this_thread::sleep_for(std::chrono::seconds(4));

    ChatMsg::ConstPtr chat3 = ChatMsg::ConstPtr(new ChatMsg("Hello I am publishAsync!"));
    EventBus::publishAsync<ChatMsg>(chat3);
}

