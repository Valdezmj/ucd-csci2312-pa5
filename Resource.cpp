//
// Created by Michael Valdez on 12/13/15.
//
#include "Resource.h"
#include "Simple.h"
#include "Advantage.h"

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

    Piece& Resource::interact(Agent * a) {
        if (this->getType() == PieceType::ADVANTAGE) {
            dynamic_cast<Simple *>(a)->addEnergy(dynamic_cast<Advantage *>(this)->consume());
        } else {
            dynamic_cast<Simple *>(a)->addEnergy(this->consume());
        }
        this->finish();
        this->__capacity = 0.0;
        return *this;
    }

    Piece& Resource::interact(Resource * r) {
        return *this;
    }

    double Resource::consume() {
        double temp = this->__capacity;
        this->__capacity = 0.0;
        this->finish();
        return temp;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return ActionType::STAY;
    }


}