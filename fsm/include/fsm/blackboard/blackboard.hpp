#ifndef BLACKBOARD_HPP_
#define BLACKBOARD_HPP_

#include "fsm/blackboard/value.hpp"

#include <unordered_map>
#include <memory>
#include <string>

namespace fsm {

class Blackboard {
public:

    Blackboard() = default;

    ~Blackboard() {
        for (auto& [key, value] : values_)
            delete value;
    }

    template <typename T>
    void set(const std::string& key, T* value) {
        
        auto it = values_.find(key);

        if (it == values_.end()) {
            this->values_.emplace(key, new Value(value));
        }
        else {
            //((Value<T> *)this->values_.at(key))->set(value);
            ((Value<T> *)it->second)->set(value);
        }

    }

    template <typename T>
    void set(const std::string& key, T value) {
        
        auto it = values_.find(key);

        if (it == values_.end()) {
            this->values_.emplace(key, new Value(value));
        }
        else {
            //((Value<T> *)this->values_.at(key))->set(value);
            ((Value<T> *)it->second)->set(value);
        }

    }

    template <typename T>
    T* get(const std::string& key) {
        
        auto it = values_.find(key);

        if (it == values_.end())
            return nullptr;
        
        return ((Value<T> *)it->second)->get();
    }

private:
    std::unordered_map<std::string, ValueBase*> values_;
};

}; // namespace fsm




#endif