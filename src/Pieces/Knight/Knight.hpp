class Knight : Piece
{
    public:
        Knight(Enums::Side side);
        
        bool ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const override;
        std::wstring GetUni() const override;

        ~Knight() = default;
};