#include "Queen.hpp"

// Constructor
Queen::Queen(Enums::Side side) 
 : Piece(side)
{}

// Methods
bool Queen::ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const
{
    return possibleMove
            && (target.GetX() == source.GetX() || target.GetY() == source.GetY() // Rook-like move
                || abs(target.GetX() - source.GetX()) == abs(target.GetY() - source.GetY())); // Bishop-like move
}

std::wstring Queen::GetUni() const
{
    return Side == Enums::Side::White ? L"♕" : L"♛";
}