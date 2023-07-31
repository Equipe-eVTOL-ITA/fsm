#include "fsm/state.hpp"

using namespace fsm;

void State::add_transition(const std::string &outcome, const std::string &next_state) {
    transitions_.emplace(outcome, next_state);
}

void State::add_transitions(const std::unordered_map<std::string,std::string> &transitions) {
    transitions_.insert(transitions.begin(), transitions.end());
}

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