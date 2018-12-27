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
};

void onEvent(ChatMsg &e) {
    std::cout << "The msg:" << e.msg << std::endl;
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

    ChatMsg chat1("Hello I am Player 1!");
    EventBus::publish<ChatMsg>(chat1);

    ChatMsg chat2("Hello I am Player 2!");
    EventBus::publish(chat2);

    ChatMsg chat3("publishAsync");
    EventBus::publishAsync<ChatMsg>(chat3);
}


