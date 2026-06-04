#include "Pawn.hpp"
// Constructor
Pawn::Pawn(Enums::Side side) 
 : Piece(side)
{}

// Methods
bool Pawn::ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const
{
    const auto relativeSource = source.GetRelativeCoords(Side);
    const auto relativeTarget = target.GetRelativeCoords(Side);
    
    if (possibleMove)
    {
        if (relativeTarget.GetY() == relativeSource.GetY() + 1
        && abs(relativeTarget.GetX() - relativeSource.GetX()) == 1)
        {
            return true;
            }
        }
        else if (relativeTarget.GetX() == relativeSource.GetX())
        {
            if (relativeTarget.GetY() == relativeSource.GetY() + 1 // Regular move
            || MovesCounter == 0 && relativeTarget.GetY() == relativeSource.GetY() + 2) // First move
            {
                return true;
            }
        }
        
        return false;
    }

std::wstring Pawn::GetUni() const
{
    return Side == Enums::Side::White ? L"♙" : L"♟";
}