#include <memory>

class Field {
    public:
        Field(const int x, const int y);
        
        bool IsOccupied() const;

        const Coords Coords_;
        std::shared_ptr<Piece> StandingPiece;

        ~Field() = default;
};