#include "Location.h"

Location::Location(int x_val, int y_val)
{
    x = x_val;
    y = y_val;
}

int Location::GetX() const
{
    return x;
}

int Location::GetY() const
{
    return y;
}

void Location::SetX(int x_val)
{
    x = x_val;
}

void Location::SetY(int y_val)
{
    y = y_val;
}