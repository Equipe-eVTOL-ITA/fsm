#include "fsm/fsm.hpp"
#include <iostream>

using namespace fsm;

class FooState : public State {
public:
    FooState() : State({{"%10", "BAR"},{">100", "FINISHED"}}) {}

    std::string act(Blackboard &blackboard) override {
        (void) blackboard;
        int* foo_counter_ptr = blackboard.get<int>("foo_counter");
        //blackboard.set<int>("foo_counter", *foo_counter_ptr + 1);
        
        if ((*foo_counter_ptr % 10) == 0)
            return "%10";
        
        if ((*foo_counter_ptr > 100) == 0)
            return ">100";

        return ""; // it will on FooState
    }

};

class BarState : public State {
public:
    BarState() : State({{"TRUE", "FOO"}}), counter_{0} {}

    std::string act(Blackboard &blackboard) override {
        (void) blackboard;
        counter_++;
        int* foo_counter_ptr = blackboard.get<int>("foo_counter");
        std::cout << "[BAR STATE " + std::to_string(counter_) + "] " << *foo_counter_ptr << std::endl;
        return "TRUE";
    }
private: 
    int counter_;
};

class CounterFSM : public FSM {
public:
    CounterFSM() : FSM({"FINISHED"}) {
        //this->blackboard_set<int>("foo_counter", new int(0));
    }
};

int main() {
    CounterFSM counter_fsm;
    counter_fsm.add_state("FOO", std::make_unique<FooState>());
    counter_fsm.add_state("BAR", std::make_unique<BarState>());

    while (!counter_fsm.is_finished())
        counter_fsm.execute();

    std::cout << counter_fsm.get_fsm_outcome() << std::endl;
}