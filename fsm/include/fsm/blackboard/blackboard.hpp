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
    ~Blackboard();

    template <typename T>
    void set(const std::string& key, T* value) {
        
        if (this->contains(key))
            ((Value<T> *)this->values_.at(key))->set(value);
        else 
            this->values_.insert({key, new Value<T>(value)});


    }

    template <typename T>
    void set(const std::string& key, T value) {

        if (this->contains(key))
            ((Value<T> *)this->values_.at(key))->set(value);
        else
            this->values_.emplace(key, new Value<T>(value));

    }

    template <typename T>
    T* get(const std::string& key) {
        
        if(this->contains(key)) {
            return ((Value<T> *)this->values_.at(key))->get();
        }
        return nullptr;
    }

    bool contains(const std::string& key);

private:
    std::unordered_map<std::string, ValueBase*> values_;
};

}; // namespace fsm




#endif