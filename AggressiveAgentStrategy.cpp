//
// Created by Michael Valdez on 12/14/15.
//
#include "AggressiveAgentStrategy.h"
#include "Game.h"
namespace Gaming {
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        PositionRandomizer __r;
        int indexToMoveTo = 0;
        std::vector<int> pos;
        if (__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC) {
                    pos.push_back(i);
                }
            }
        } else {
            if (pos.size() == 0) {
                for (int i = 0; i < 9; i++) {
                    if (s.array[i] == PieceType::ADVANTAGE) {
                        pos.push_back(i);
                    }
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::FOOD) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::EMPTY) {
                    pos.push_back(i);
                }
            }
            if (pos.size() > 0) {

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