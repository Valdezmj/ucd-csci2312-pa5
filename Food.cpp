//
// Created by Michael Valdez on 12/13/15.
//
#include "Food.h"

namespace Gaming {

    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {
        //std::cout << "Food constructor\n";
        __capacity = capacity;

    }
    Food::~Food() {
        //std::cout << "Food deconstructor\n";

    }

    void Food::print(std::ostream &os) const {
        os << FOOD_ID << this->__id;
    }
}