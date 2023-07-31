#ifndef STATE_HPP_
#define STATE_HPP_

#include "fsm/blackboard/blackboard.hpp"

#include <string>
#include <unordered_map>
#include <memory>

namespace fsm {

class State
{
public:
    State() = default;
private:

    void add_transition(const std::string &outcome, const std::string &next_state);
    void add_transitions(const std::unordered_map<std::string,std::string> &transitions);
    const std::unordered_map<std::string,std::string>& get_transitions();

    virtual std::string act(Blackboard &blackboard) = 0;
    virtual void on_enter(Blackboard &blackboard);
    virtual void on_exit(Blackboard &blackboard);
    virtual std::string to_string();


    // transitions maps the outcome to the next state
    std::unordered_map<std::string,std::string> transitions_;

    friend class FSM;
};

}; // namespace fsm

#endif