#pragma once

#include "ThreadPool.h"

#include <list>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>

namespace eventbus {
    template<class T>
    using Callback = std::function<void(T &)>;

    struct Object {

    };

    template<typename T>
    struct CallbackHolder : public Object {
        std::list<Callback<T>> callback_list;
    };

    class EventBus {
    public:
        EventBus() {
            pool_ = std::make_shared<ThreadPool>(4);
        }

        virtual ~EventBus() = default;

        static EventBus *getInstance() {
            static EventBus instance;
            return &instance;
        }

        template<class T>
        static void subscribe(const Callback<T> &callback) {
            std::unique_ptr<Object> &callbacks_ptr = getInstance()->callbacks_[typeid(T)];
            if (callbacks_ptr == nullptr) {
                callbacks_ptr.reset(new CallbackHolder<T>{});
            }
            auto *holder = static_cast<CallbackHolder<T> *>(callbacks_ptr.get());
            holder->callback_list.push_back(callback);
        }

        template<class T>
        static void publish(T &e) {
            std::unique_ptr<Object> &callbacks_ptr = getInstance()->callbacks_[typeid(e)];
            if (callbacks_ptr == nullptr) {
                return;
            }
            auto *holder = static_cast<CallbackHolder<T> *>(callbacks_ptr.get());
            for (auto callback : holder->callback_list) {
                callback(e);
            }
        }

        template<class T>
        static void publishAsync(T &e) {
            std::unique_ptr<Object> &callbacks_ptr = getInstance()->callbacks_[typeid(e)];
            if (callbacks_ptr == nullptr) {
                return;
            }
            auto *holder = static_cast<CallbackHolder<T> *>(callbacks_ptr.get());
            for (auto callback : holder->callback_list) {
                getInstance()->pool_->execute(callback, e);
            }
        }


    private:
        std::shared_ptr<ThreadPool> pool_;

        std::map<std::type_index, std::unique_ptr<Object>> callbacks_;

    };
}

