#pragma once

class Behaviour
{
public:
    Behaviour();
    ~Behaviour();

    enum state
    {
        none,
        seek,
        flee,
        arrive,
        wander,
    };

    state _state;

private:
    
};

