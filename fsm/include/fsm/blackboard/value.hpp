#ifndef VALUE_HPP_
#define VALUE_HPP_

#include "fsm/blackboard/value_base.hpp"

namespace fsm {

template <typename T>
class Value : public ValueBase {
public:
    Value(T* value) : value_{value} {}
    Value(T value) : value_{new T(value)} {}

    ~Value() {
        delete this->value_;
    }

    T* get() {
        return this->value_;
    }

    void set(T* value) {
        delete this->value_; 
        this->value_ = value; 
    }

    void set(T value) {
        delete this->value_; 
        this->value_ = new T(value); 
    }

private:
    T* value_;

friend class Blackboard;

};

}; // namespace fsm

#endif