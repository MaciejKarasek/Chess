#include "Enums.hpp"

class Coords {
    public:
        Coords(const int x, const int y);

        int GetX() const;
        int GetY() const;
        int GetRelativeX(const Enums::Side side) const;
        int GetRelativeY(const Enums::Side side) const;
        Coords GetRelativeCoords(const Enums::Side side) const;
        
    private:
        const int X;
        const int Y;
};
