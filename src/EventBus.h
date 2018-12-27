#pragma once

#include <list>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>
#include <thread>

#include "ThreadPool.h"

namespace eventbus {
    template<class T>
    using ConstPtr = std::shared_ptr<T const>;

    template<class T>
    using Callback = std::function<void(ConstPtr<T>)>;

    struct BaseCallbacks {};

    template<typename T>
    struct ListCallbacks : public BaseCallbacks {
        std::list<Callback<T>> callback_list;
    };

    class EventBus {
    public:
        EventBus() {
            pool_ = std::make_shared<ThreadPool>(std::thread::hardware_concurrency());
        }

        virtual ~EventBus() = default;

        static EventBus *getInstance() {
            static EventBus instance;
            return &instance;
        }

        template<class T>
        static void subscribe(const Callback<T> &callback) {
            std::unique_ptr<BaseCallbacks> &callbacks_ptr = getInstance()->callbacks_[typeid(T)];
            if (callbacks_ptr == nullptr) {
                callbacks_ptr.reset(new ListCallbacks<T>{});
            }
            auto *holder = static_cast<ListCallbacks<T> *>(callbacks_ptr.get());
            holder->callback_list.push_back(callback);
        }

        template<class T>
        static void publish(ConstPtr<T> e) {
            std::unique_ptr<BaseCallbacks> &callbacks_ptr = getInstance()->callbacks_[typeid(T)];
            if (callbacks_ptr == nullptr) {
                return;
            }
            auto *holder = static_cast<ListCallbacks<T> *>(callbacks_ptr.get());
            for (auto callback : holder->callback_list) {
                callback(e);
            }
        }

        template<class T>
        static void publishAsync(ConstPtr<T> e) {
            std::unique_ptr<BaseCallbacks> &callbacks_ptr = getInstance()->callbacks_[typeid(T)];
            if (callbacks_ptr == nullptr) {
                return;
            }

            auto *holder = static_cast<ListCallbacks<T> *>(callbacks_ptr.get());
            for (auto callback : holder->callback_list) {
                getInstance()->pool_->execute(callback, e);
            }
        }

    private:
        std::shared_ptr<ThreadPool> pool_;
        std::map<std::type_index, std::unique_ptr<BaseCallbacks>> callbacks_;

    };
}

