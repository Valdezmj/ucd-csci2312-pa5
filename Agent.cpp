//
// Created by Michael Valdez on 12/13/15.
//
#include "Agent.h"

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

    Piece& Agent::interact(Agent *) {

    }

    Piece& Agent::interact(Resource *) {

    }

    Piece& Agent::operator*(Piece &other) {

    }

}