//
// Created by Michael Valdez on 12/13/15.
//
#include "Resource.h"

namespace Gaming {

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;


    Resource::Resource(const Game &g, const Position &p, double __capacity) : Piece(g, p) {
        //std::cout << "Resource constructor\n";
        this->__capacity = __capacity;

    }

    Resource::~Resource() {
        //std::cout << "Resource deconstructor\n";

    }

    Piece& Resource::operator*(Piece &other) {

    }

    void Resource::age() {
        if (__capacity <= .0001) {
            __capacity = 0;
            this->finish();
        } else {
            __capacity /= RESOURCE_SPOIL_FACTOR;
        }
    }

    Piece& Resource::interact(Agent *) {

    }

    Piece& Resource::interact(Resource *) {

    }

    double Resource::consume() {

    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return ActionType::STAY;
    }


}