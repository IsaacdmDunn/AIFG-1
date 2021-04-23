#include "Behaviour.h"

Behaviour::Behaviour()
{
    
}

Behaviour::~Behaviour()
{
}

Vector2D Behaviour::Seek(Vector2D TargetPosition)
{
    return Vector2D();
}

Vector2D Behaviour::Flee(Vector2D TargetPosition)
{
    return Vector2D();
}

Vector2D Behaviour::Arrive(Vector2D TargetPosition)
{
    return Vector2D();
}

Vector2D Behaviour::Pursuit(Car pursuitTarget)
{
    return Vector2D();
}

Vector2D Behaviour::Wander()
{
    return Vector2D();
}
