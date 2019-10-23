# Statless4cpp
Statless State Machine Implementation in C++

Possible Usage:


    typedef statemachine::StateMachineConfiguration<ProcessController::States, ProcessController::StateTrigger> ConfigType;
    typedef statemachine::StateConfiguration<ProcessController::States, ProcessController::StateTrigger> StateConfigurationType;
    typedef statemachine::StateMachine<States,StateTrigger> StateMachineType;

    StateMachineType machine;
    ConfigType createConfiguration();

ProcessController::ConfigType ProcessController::createConfiguration()
{
    ConfigType config;

    config[READY] = StateConfigurationType();
    config[READY].stateTransitions[ON_MODE_CHANGE_DETECTED] = BEFORE_NEW_MODE_SELECTED;

    config[BEFORE_NEW_MODE_SELECTED].stateTransitions[ON_MODE_CHANGE_TO_RECORD] = WAIT_FOR_RECORD_START;
    config[BEFORE_NEW_MODE_SELECTED].onEntry = [this](){ this->onModeSelect(); };

    config[WAIT_FOR_RECORD_START] = StateConfigurationType();
    config[WAIT_FOR_RECORD_START].stateTransitions[ON_ACQUISITION_START] = RECORD_IN_PROGRESS;

    return config;
}

Please ask for more details, if needed!
