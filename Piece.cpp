//
// Created by Michael Valdez on 12/13/15.
//
#include "Piece.h"

namespace Gaming {
    unsigned int Piece::__idGen = 0;
    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p) {
        __id = __idGen;
        __idGen++;
        __finished = false;
        //std::cout << "Piece constructor - id: " << __id << std::endl;
    }

    Piece::~Piece() {
        __idGen--;

    }

     std::ostream & operator<<(std::ostream &os, const Piece &piece) {
        piece.print(os);
         return os;
    }
}