namespace Enums
{
    enum class PieceType : int
    {
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King,
    };
    
    enum class Side : int
    {
        White,
        Black,
        None,
    };

    enum class Row : int // weird but it is what it is
    {
        _1 = 0,
        _2 = 1,
        _3 = 2,
        _4 = 3,
    };

    enum class Column : int
    {
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        G = 6,
        H = 7,
    };
}