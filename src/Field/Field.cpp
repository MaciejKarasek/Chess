#include "Field.hpp"

// Pieces
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"
// Pieces

// Helper functions
bool IsNthRow(const Enums::Row row, const int y)
{
    const auto intRow = static_cast<int>(row);

    return y == intRow || y == 8 - intRow;
}

Enums::Side GetSide(const int y)
{
    return y <= 1 ? Enums::Side::White : Enums::Side::Black;
}
// Helper functions

Field::Field(const int x, const int y)
    : Coords_(x, y)
{
    const auto side = GetSide(y);

    if (IsNthRow(Enums::Row::_2, y))
    {
        StandingPiece = std::make_shared<Pawn>(side);
    }
    else if (IsNthRow(Enums::Row::_1, y))
    {
        const auto xEnum = static_cast<Enums::Column>(x);
        
        if (xEnum == Enums::Column::B || xEnum == Enums::Column::G)
            StandingPiece = std::make_shared<Knight>(side);
        else if (xEnum == Enums::Column::C || xEnum == Enums::Column::F)
            StandingPiece = std::make_shared<Bishop>(side);
        else if (xEnum == Enums::Column::A || xEnum == Enums::Column::H)
            StandingPiece = std::make_shared<Rook>(side);
        else if (xEnum == Enums::Column::D)
            StandingPiece = std::make_shared<Queen>(side);
        else if (xEnum == Enums::Column::E)
            StandingPiece = std::make_shared<King>(side);
        else
            StandingPiece = std::make_shared<Piece>(side);
    }
}
        
bool Field::IsOccupied() const
{
    return !(StandingPiece->Side == Enums::Side::None);
}