//
// Created by Michael Valdez on 12/13/15.
//
#include "Simple.h"

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';


    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) {
        //std::cout << "Simple constructor\n";

    }
    Simple::~Simple() {
        //std::cout << "Simple deconstructor\n";

    }

    void Simple::print(std::ostream &os) const {
        os << SIMPLE_ID << this->__id;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        PositionRandomizer __r;
        int indexToMoveTo = 0;
        std::vector<int> pos;
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD) {
                pos.push_back(i);
            }
        }

        if (pos.empty()) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::EMPTY) {
                    std::cout << "Adding empty spot: " << i << "\n";
                    pos.push_back(i);
                }
            }
        }

        if (pos.empty()) {
            std::cout << "Returning stay\n";
            return ActionType::STAY;
        }
        pos.shrink_to_fit();

        if (pos.size() == 1) {
            std::cout << "size of pos : 1\n";
            indexToMoveTo = pos.back();
        } else {
            std::cout << "size of pos: " << pos.size() << std::endl;
            indexToMoveTo = positionToIndex(__r(pos), __game.getWidth());
        }
        std::cout << "index move to: " << indexToMoveTo << std::endl;
        switch (indexToMoveTo) {
            case 0:
            std::cout << "Heading north west\n";
                return ActionType::NW;
            case 1:
                return ActionType::N;
            case 2:
                return ActionType::NE;
            case 3:
                return ActionType::W;
            case 5:
                return ActionType::E;
            case 6:
                return ActionType::SW;
            case 7:
                return ActionType::S;
            case 8:
                return ActionType::SE;
        }
    }

}