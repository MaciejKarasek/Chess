#include "Knight.hpp"

// Constructor
Knight::Knight(Enums::Side side) 
 : Piece(side)
{}

// Methods
bool Knight::ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const
{
    const auto validateMove = [](const Coords& source, const Coords& target)
    {
        return (abs(target.GetX() - source.GetX()) == 2 && abs(target.GetY() - source.GetY()) == 1)
                || (abs(target.GetX() - source.GetX()) == 1 && abs(target.GetY() - source.GetY()) == 2);
    };

    return possibleMove && validateMove(source.GetRelativeCoords(Side), target.GetRelativeCoords(Side));
}

std::wstring Knight::GetUni() const
{
    return Side == Enums::Side::White ? L"♘" : L"♞";
}