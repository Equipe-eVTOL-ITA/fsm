#include "fsm/fsm.hpp"

#include <string>
#include <iostream>
#include <memory>

using namespace fsm;


class FooState : public State {
public:
    FooState() : State(), counter_{0} {}

    std::string act(Blackboard &blackboard) override {
        (void)blackboard;
        counter_++;

        if (counter_ > 15)
            return ">15";

        return ""; // it will on FooState
    }

    void on_enter(Blackboard &blackboard) override {
        (void)blackboard;
        std::cout << "Entering FooState.\n";
    }

    void on_exit(Blackboard &blackboard) override {
        (void)blackboard;
        std::cout << "Exiting FooState.\n";
        std::cout << "Counter = " << this->counter_ << std::endl;
    }

private:
    int counter_;
};

int main() {
    FSM counter_fsm({"FINISHED"});
    counter_fsm.add_state("FOO", std::make_unique<FooState>());
    counter_fsm.add_transition("FOO", ">15", "FINISHED");

    while (!counter_fsm.is_finished())
        counter_fsm.execute();

    std::cout << counter_fsm.get_fsm_outcome() << std::endl;
}