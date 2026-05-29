class Bishop : Piece
{
    public:
        Bishop(Enums::Side side);

        bool ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const override;
        std::wstring GetUni() const override;

        ~Bishop() = default;
};