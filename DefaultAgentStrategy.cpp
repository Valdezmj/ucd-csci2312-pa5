//
// Created by Michael Valdez on 12/13/15.
//
#include "DefaultAgentStrategy.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() {

    }

    DefaultAgentStrategy::~DefaultAgentStrategy() {

    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        PositionRandomizer __r;
        int indexToMoveTo = 0;
        std::vector<int> pos;
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == PieceType::ADVANTAGE) {
                pos.push_back(i);
            }
        }

        if (pos.empty()) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::FOOD) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.empty()) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::EMPTY) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.empty()) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::SIMPLE) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            return ActionType::STAY;
        }

        if (pos.size() == 1) {
            indexToMoveTo = pos[0];
        } else {
            indexToMoveTo = positionToIndex(__r(pos), 3);
        }

        switch (indexToMoveTo) {
            case 0:
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