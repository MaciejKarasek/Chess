#include "King.hpp"

// Constructor
King::King(Enums::Side side) 
 : Piece(side)
{}

// Methods
bool King::ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const
{
    return possibleMove && abs(target.GetX() - source.GetX()) <= 1 && abs(target.GetY() - source.GetY()) <= 1;
}

std::wstring King::GetUni() const
{
    return Side == Enums::Side::White ? L"♔" : L"♚";
}
