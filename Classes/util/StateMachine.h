#ifndef CPP_DEMO_STATE_MACHINE_H
#define CPP_DEMO_STATE_MACHINE_H

template <typename T>
class State
{
public:
    virtual void onEnterState() = 0;
    virtual void onExecuteState() = 0;
    virtual void onExitState() = 0;
};

template <typename T>
class StateMachine
{
public:

    void changeState(State<T> *newState);
    void update();
    State<T>* currentState() const
    {
        return currentState_;
    }

private:
    State<T>    *currentState_;
};

template <typename T>
void StateMachine<T>::changeState(State<T> *newState)
{
    if (currentState_)
    {
        currentState_->onExitState();
    }

    if (newState)
    {
        newState->onEnterState();
        currentState_ = newState;
    }
}

template <typename T>
void StateMachine<T>::update()
{
    if (currentState_)
    {
        currentState_->onExecuteState();
    }
}

#endif