#ifndef FIELD_HPP
#define FIELD_HPP

#ifndef LIBARIES
#define LIBARIES
#include <string>
#include <iostream>
#include <vector>
#include <map>
#endif // LIBARIES

#include "Piece.hpp"

class Field {
    public:
        Field();
        bool occupied; // 1 -> Piece standing on field, else -> 0
        Piece piece;
        void setvalues(int tp, int cr);
        void setvalues(const Field& other);
        ~Field();
};

#endif // FIELD_HPP