#include "fsm/fsm.hpp"
#include <iostream>

using namespace fsm;

class FooState : public State {
public:
    FooState() : State({{"%10", "BAR"},
                        {">100", "FINISHED"},
                        {"SEG_FAULT", "SEG_FAULT"}}) {}

    std::string act(Blackboard &blackboard) override {

        int* foo_counter_ptr = blackboard.get<int>("foo_counter");
        if (foo_counter_ptr == nullptr) return "SEG_FAULT"; // always check

        blackboard.set<int>("foo_counter", *foo_counter_ptr + 1);
        
        if ((*foo_counter_ptr % 10) == 0)
            return "%10";
        
        if (*foo_counter_ptr > 100)
            return ">100";

        return ""; // it will on FooState
    }

};

class BarState : public State {
public:
    BarState() : State({{"TRUE", "FOO"},
                        {"SEG_FAULT", "SEG_FAULT"}}), 
                counter_{0} {}

    std::string act(Blackboard &blackboard) override {

        counter_++;

        int* foo_counter_ptr = blackboard.get<int>("foo_counter");
        if (foo_counter_ptr == nullptr) return "TRUE"; // always check return

        std::cout << "[BAR STATE " + std::to_string(counter_) + "] " << *foo_counter_ptr << std::endl;

        return "TRUE";
    }
private: 
    int counter_;
};

class CounterFSM : public FSM {
public:
    CounterFSM() : FSM({"FINISHED","SEG_FAULT"}) {
        this->blackboard_set<int>("foo_counter", 0);
    }
};

int main() {
    CounterFSM counter_fsm;
    counter_fsm.add_state("FOO", std::make_unique<FooState>());
    counter_fsm.add_state("BAR", std::make_unique<BarState>());

    while (!counter_fsm.is_finished())
        counter_fsm.execute();

    std::cout << counter_fsm.get_fsm_outcome()
              << std::endl  
              << "[foo_counter] : "
              << *counter_fsm.blackboard_get<int>("foo_counter")
              << std::endl;
}