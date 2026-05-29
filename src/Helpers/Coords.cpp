Coords::Coords(const int x, const int y)
    : X(x), Y(y)
    {}

int Coords::GetX() const
{
        return X;
}

int Coords::GetY() const
{
        return Y;
}

int Coords::GetRelativeX(const Enums::Side side) const
{
    if (side == Enums::Side::White) 
        return X;
    else
        return 7 - X;
}

int Coords::GetRelativeY(const Enums::Side side) const
{
    if (side == Enums::Side::White) 
        return Y;
    else
        return 7 - Y;
}

Coords Coords::GetRelativeCoords(const Enums::Side side) const
{
    return {GetRelativeX(side), GetRelativeY(side)};
}