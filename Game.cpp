//
// Created by Michael Valdez on 12/12/15.
//
#include "Game.h"
#include "Piece.h"
#include "Advantage.h"
#include "Simple.h"
#include "Food.h"
#include "Strategic.h"
#include <iostream>
namespace Gaming {

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;



    Game::Game() {
        __width  = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __grid.resize(__width * __height);
        __status = Status::NOT_STARTED;
        //std::cout << "Game created with size - " << __grid.size() << std::endl;
        //std::cout << "Game created\n" << std::endl;
    }

    Game::Game(unsigned width, unsigned height, bool manual) {
        __width = width;
        __height = height;
        __grid.resize(__width * __height);
        if (manual == false) {
            populate();
        }
    }

    Game::~Game() {
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {
                std::cout << "deleting object " << *(__grid[i]) << std::endl;
                std::cout << "Type: ";
                switch ((__grid[i])->getType()) {
                    case PieceType::FOOD:
                        std::cout << "Food\n";
                        break;
                    case PieceType::ADVANTAGE:
                        std::cout << "Advantage\n";
                        break;
                    case PieceType::SIMPLE:
                        break;
                    case PieceType::STRATEGIC:
                        std::cout << "Strategic\n";
                        break;
                }
            }
            delete __grid[i];
        }
        //std::cout << "Game destroyed\n" << std::endl;
    }

    bool Game::addAdvantage(const Position &position) {
        std::cout << "adding advantage to game\n";
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            std::cout << "adding advantage to game\n";
            Piece * p = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(position, __width)] = p;
            return true;
        }
        return false;
    }

    bool Game::addAdvantage(unsigned x, unsigned y) {
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            Piece *__piece = new Advantage(*this, p, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addSimple(const Position &position) {
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            Piece *__piece = new Simple(*this, position, STARTING_AGENT_ENERGY);
            __grid.push_back(__piece);
            return true;
        }
        return false;
    }

    bool Game::addSimple(unsigned x, unsigned y) {
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            Piece *__piece = new Simple(*this, p, STARTING_AGENT_ENERGY);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addFood(const Position & position) {
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            Piece *__piece = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(position, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addFood(unsigned x, unsigned y) {
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            Piece *__piece = new Food(*this, p, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            Piece *__piece = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
            __grid[Gaming::positionToIndex(position, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            Piece *__piece = new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings s;
        int indexOfPiece = Gaming::positionToIndex(pos, __width);
        std::cout << "getting surrounds of index - " << indexOfPiece << std::endl;
        std::vector<Position> indexToCheck;
        Position temp(0,0);
        int x = pos.x, y = pos.y;
        if (indexOfPiece < __grid.size() && indexOfPiece >= 0) {
            // Get array of all indexes of surroundings
            int __i = 0;
            for (int i = -1; i <= 1; i++) {
                for (int k = -1; k <= 1; k++) {
                    if (__i == 4) {
                        s.array[__i] = PieceType::SELF;
                    } else {
                        if (x + i < 0 || x + i >= __width) {
                            s.array[__i] = PieceType::INACCESSIBLE;
                        } else if (y + k < 0 || y + k >= __height) {
                            s.array[__i] = PieceType::INACCESSIBLE;
                        } else {
                            temp.x = pos.x + i;
                            temp.y = pos.y + k;
                            if (__grid[positionToIndex(temp, __width)] != nullptr) {
                                s.array[__i] = __grid[positionToIndex(temp, __width)]->getType();
                            } else {
                                s.array[__i] = PieceType::EMPTY;
                            }
                        }
                    }
                    __i++;
                }
            }

        } else {
            for (int i  = 0; i < 9; i++) {
                if (i != 4) {
                    s.array[i] = PieceType::INACCESSIBLE;
                } else {
                    s.array[i] = PieceType::SELF;
                }
            }
        }
        return s;
    }

    void Game::populate() {

    }
}