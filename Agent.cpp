//
// Created by Michael Valdez on 12/13/15.
//
#include "Agent.h"
#include "Resource.h"
#include "Advantage.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;



    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {
        __energy = energy;

    }

    Agent::~Agent() {

    }

    void Agent::age() {
        if (__energy <= .0001) {
            __energy = 0;
            this->finish();
        } else {
            __energy *= AGENT_FATIGUE_RATE;
        }
    }

    Piece& Agent::interact(Agent * a) {
        if (a->__energy > this->__energy) {
            a->__energy -= this->__energy;
            this->__energy = 0.0;
            this->finish();
            return *a;
        } else if (a->__energy < this->__energy) {
            this->__energy -= a->__energy;
            a->__energy = 0.0;
            a->finish();
            return *this;
        } else {
            a->__energy = 0.0;
            a->finish();
            this->__energy = 0.0;
            this->finish();
            return *this;
        }
    }

    Piece& Agent::interact(Resource * r) {
        this->__energy += r->consume();
        return *this;
    }

    Piece& Agent::operator*(Piece &other) {
        if (other.getType() == PieceType::SIMPLE || other.getType() == PieceType::STRATEGIC) {
            return interact(dynamic_cast<Agent *>(&other));
        } else if (other.getType() == PieceType::FOOD || other.getType() == PieceType::ADVANTAGE) {
            return interact(dynamic_cast<Resource *>(&other));
        }
    }
}