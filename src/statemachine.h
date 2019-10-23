#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <functional>
#include <map>

namespace statemachine {

template<class S, class T>
struct StateConfiguration{
    std::function<void()> onEntry;
    std::function<void()> onExit;
    std::map<T,S> stateTransitions;

    StateConfiguration() : onEntry([](){}), onExit([](){}) {}
};

template<class S, class T>
struct StateMachineConfiguration : public std::map<S,StateConfiguration<S,T>> {};

struct IllegalStateTransition : public std::runtime_error{
    explicit IllegalStateTransition(const std::string& __arg) : std::runtime_error(__arg) {}
};

template<class S, class T>
class StateMachine {
public:
    StateMachine(const S &startState, const StateMachineConfiguration<S,T> &configuration) :
        currentState(startState), states(configuration)
    {
        states[currentState].onEntry();
    }

    void onTrigger(const T &trigger){
        if(states[currentState].stateTransitions.count(trigger) != 1){
            throw IllegalStateTransition("<Text>");
        }else{
            if(currentState != states[currentState].stateTransitions[trigger]){
                states[currentState].onExit();
                currentState = states[currentState].stateTransitions[trigger];
                states[currentState].onEntry();
            }
        }
    }

private:
    S currentState;
    StateMachineConfiguration<S,T> states;
};

}

#endif // STATEMACHINE_H
