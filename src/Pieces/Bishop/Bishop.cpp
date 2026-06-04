#include "Bishop.hpp"

// Constructor
Bishop::Bishop(Enums::Side side) 
 : Piece(side)
{}

// Methods
bool Bishop::ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const
{
    return possibleMove && abs(target.GetX() - source.GetX()) == abs(target.GetY() - source.GetY());
}

std::wstring Bishop::GetUni() const
{
    return Side == Enums::Side::White ? L"♗" : L"♝";
}