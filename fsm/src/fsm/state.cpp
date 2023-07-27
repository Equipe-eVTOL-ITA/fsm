#include "fsm/state.hpp"

using namespace fsm;

State::State(std::unordered_map<std::string,std::string> transitions) : transitions_{transitions} {}

const std::unordered_map<std::string,std::string>& State::get_transitions() {
    return transitions_;
}

void State::on_enter(Blackboard &blackboard) {
    (void)blackboard;
}

void State::on_exit(Blackboard &blackboard) {
    (void)blackboard;
}

std::string State::to_string() {
    return "";
}