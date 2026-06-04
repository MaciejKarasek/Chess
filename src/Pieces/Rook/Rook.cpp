#include "Rook.hpp"

// Constructor
Rook::Rook(Enums::Side side) 
 : Piece(side)
{}

// Methods
bool Rook::ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const
{
    return possibleMove && (target.GetX() == source.GetX() || target.GetY() == source.GetY());
}

std::wstring Rook::GetUni() const
{
    return Side == Enums::Side::White ? L"♖" : L"♜";
}