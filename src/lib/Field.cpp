#include "Field.hpp"

Field::Field() 
{
    occupied = 0;
}

void Field::setvalues(int tp, int cr) 
{
    if (tp != 0) {
        occupied = 1; 
        piece.setvalues(tp, cr);
    } else {
        occupied = 0;
        piece.setvalues(tp, cr);
    }
}

void Field::setvalues(const Field& other) 
{
    occupied = other.occupied;
    piece.setvalues(other.piece);
}

Field::~Field() = default;