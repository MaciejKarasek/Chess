#include <string>
#include <stdexcept>

class Piece
{
    public:
        Piece(Enums::Side side = Enums::Side::None);

        static bool IsPossibleMove(const bool occupied, const Enums::Side sourceSide, const Enums::Side targetSide);

        const Enums::Side Side;
        int MovesCounter = 0;

        void setColor(int cr);
        virtual bool ValidateMove(const bool possibleMove, const Coords& source, const Coords& target) const;
        virtual std::wstring GetUni() const;

        ~Piece() = default;
};