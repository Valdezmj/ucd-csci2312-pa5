//
// Created by Michael Valdez on 12/13/15.
//
#include "Strategic.h"

namespace Gaming {

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy) {
        //std::cout << "Strategic constructor\n";
        __strategy = s;

    }

    Strategic::~Strategic() {
        //std::cout << "Strategic derconstructor\n";
        delete __strategy;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        return (*__strategy)(s);
    }

    void Strategic::print(std::ostream &os) const {
        os << STRATEGIC_ID << this->__id;
    }
}
