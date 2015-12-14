//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_GAMING_H
#define PA5GAME_GAMING_H

#include <array>
#include <random>
#include <iostream>

namespace Gaming {

    // matrix convention: x indexes rows from top to bottom, y column from left to right
    struct Position {
        unsigned int x, y;
        Position() {}
        Position(unsigned int x, unsigned int y) : x(x), y(y) {}
    };

    // actions are either a motion in one of 8 directions or staying in place
    enum ActionType { N=0, NE, NW, E, W, SE, SW, S, STAY };

    // what a position on the game grid can be filled with
    enum PieceType { SIMPLE=0, STRATEGIC, FOOD, ADVANTAGE, INACCESSIBLE, SELF, EMPTY };

    // Movement between position and index
    static const int positionToIndex(const Position &p, const unsigned __width) {
        int __index = 0;
        if (p.x > 0) {
            __index = (__width * p.x) + p.y;
        } else {
            __index = p.y;
        }

        std::cout << "accepting position (" << p.x << ", " << p.y << ") and turning to index - " << __index << std::endl;

        return __index;
    }

    static const Position indexToPosition(const unsigned int index, const unsigned __width, const unsigned __height) {
        if (index < __width) {
            return Position(0, index);
        }
        for (int i = 0; i < __height; i++) {
            if ((index % (__width + i)) == 0) {
                return Position(i, 0);
            }
            for (int k = 0; k < __width; k++) {
                if ((index % (__width + i + k)) == 0) {
                    return Position(i, k);
                }
            }
        }
    }
    // a "map" of the 8 squares adjacent to a piece
    struct Surroundings {
        // encoded as an array/vector top-left row-wise bottom-right
        // [0][1][2]
        // [3][4][5]
        // [6][7][8]
        // the piece is always at 1x1 (SELF)
        std::array<PieceType, 9> array;
    };

    class PositionRandomizer {
        std::default_random_engine __gen;
        std::uniform_int_distribution<int> *__dist[10];
    public:
        PositionRandomizer() {
            for (int i = 0; i < 10; i++)
                __dist[i] = new std::uniform_int_distribution<int>(0, i);
        }
        ~PositionRandomizer() {
            for (int i = 0; i < 10; i++) delete __dist[i];
        }
        const Position operator()(const std::vector<int> &positionIndices) { // TODO EmptyPosVectorEx
            int posIndex = (*__dist[positionIndices.size() - 1])(__gen);
            return Position(
                    (unsigned) (positionIndices[posIndex] / 3),
                    (unsigned) (positionIndices[posIndex] % 3));
        }
    };

}

#endif // PA5GAME_GAMING_H
