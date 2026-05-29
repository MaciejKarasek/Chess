// Constructor
Piece::Piece(Enums::Side side) : Side(side)
{}

// Methods
bool Piece::IsPossibleMove(const bool occupied, const Enums::Side sourceSide, const Enums::Side targetSide)
{
    return !occupied || sourceSide != targetSide;
}

std::wstring Piece::GetUni() const
{
    return L" ";
}