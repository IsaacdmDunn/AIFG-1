#pragma once

#include "Car.h"
#include "Vehicle.h"

class Behaviour
{
public:
    Behaviour();
    ~Behaviour();
    Vector2D Seek(Vector2D TargetPosition);
    Vector2D Flee(Vector2D TargetPosition);
    Vector2D Arrive(Vector2D TargetPosition); //need decel
    Vector2D Pursuit(Car pursuitTarget); 
    Vector2D Wander(); 
    


private:
    
};

