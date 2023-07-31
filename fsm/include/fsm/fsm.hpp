#ifndef FSM_HPP_
#define FSM_HPP_

#include "fsm/state.hpp"
#include "fsm/blackboard/blackboard.hpp"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>

namespace fsm {

class FSM
{
public:

    FSM(std::unordered_set<std::string> outcomes);

    void add_state(std::string name, std::unique_ptr<State> state);

    void add_transition(const std::string &current_state,
                        const std::string &transition, 
                        const std::string &next_state);

    void add_transitions(const std::string &current_state, 
                         const std::unordered_map<std::string,std::string> &transitions);

    void set_initial_state(std::string state_name);

    void execute();

    bool is_finished();

    std::string get_current_state();

    std::string get_fsm_outcome();

    template <typename T>
    void blackboard_set(const std::string& key, T* value) {
        blackboard_.set<T>(key, value);
    }

    template <typename T>
    void blackboard_set(const std::string& key, T value) {
        blackboard_.set<T>(key, value);
    }

    template <typename T>
    T* blackboard_get(const std::string& key) {
        return blackboard_.get<T>(key);
    }

private:

    void check_transition();
    bool initial_state_not_set();

    Blackboard blackboard_;
    std::unordered_map<std::string, std::unique_ptr<State>> states_;
    std::unordered_set<std::string> outcomes_;
    std::string current_state_;
    std::string last_outcome_;

    class InitialState : public State {
    public:
        InitialState();
        std::string act(Blackboard &blackboard) override;
    };
    

};

}; // namespace fsm

#endif