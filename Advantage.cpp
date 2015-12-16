//
// Created by Michael Valdez on 12/13/15.
//
#include "Advantage.h"

namespace Gaming {


    const char Advantage::ADVANTAGE_ID = 'D';

    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;




    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity * ADVANTAGE_MULT_FACTOR) {
        //std::cout << "Advantage constructor\n";
    }

    Advantage::~Advantage() {
        //std::cout << "Advantage deconstructor\n";

    }

    double Advantage::consume(){
        double temp = __capacity * ADVANTAGE_MULT_FACTOR;
        __capacity = 0.0;
        this->finish();
        return temp;
    }

    double Advantage::getCapacity() const {
        return __capacity;
    }

    void Advantage::print(std::ostream &os) const {
        os << ADVANTAGE_ID << this->__id;
    }
}
