//
// Created by Michael Valdez on 12/12/15.
//
#include "Game.h"
#include "Piece.h"
#include "Advantage.h"
#include "Simple.h"
#include "Food.h"
#include "Strategic.h"
#include "Exceptions.h"
#include <iomanip>
#include <set>
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
        __round = 0;
        //std::cout << "Game created with size - " << __grid.size() << std::endl;
        //std::cout << "Game created\n" << std::endl;
    }

    Game::Game(unsigned width, unsigned height, bool manual) {
        if (width < MIN_WIDTH || height < MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }
        __width = width;
        __height = height;
        __grid.resize(__width * __height);
        if (!manual) {
            populate();
        }
        __status = Status::NOT_STARTED;
        __round = 0;
    }

    Game::~Game() {
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {
                delete __grid[i];
            }
        }
        //std::cout << "Game destroyed\n" << std::endl;
    }

    bool Game::addAdvantage(const Position &position) {
        if (position.x >= __height || position.y >= __width) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(position, __width)] != nullptr) {
                return false;
            }
            Piece * p = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(position, __width)] = p;
            return true;
        }
        return false;
    }

    bool Game::addAdvantage(unsigned x, unsigned y) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(p, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Advantage(*this, p, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addSimple(const Position &position) {
        if (position.x >= __height || position.y >= __width) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(position, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Simple(*this, position, STARTING_AGENT_ENERGY);
            __grid[Gaming::positionToIndex(position, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addSimple(unsigned x, unsigned y) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(p, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Simple(*this, p, STARTING_AGENT_ENERGY);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addFood(const Position & position) {
        if (position.x >= __height || position.y >= __width) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(position, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(position, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addFood(unsigned x, unsigned y) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(p, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Food(*this, p, STARTING_RESOURCE_CAPACITY);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {
        if (position.x >= __height || position.y >= __width) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (Gaming::positionToIndex(position, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(position, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
            __grid[Gaming::positionToIndex(position, __width)] = __piece;
            return true;
        }
        return false;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position p(x, y);
        if (Gaming::positionToIndex(p, __width) < __grid.size()) {
            if (__grid[Gaming::positionToIndex(p, __width)] !=nullptr) {
                return false;
            }
            Piece *__piece = new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
            __grid[Gaming::positionToIndex(p, __width)] = __piece;
            return true;
        }
        return false;
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings s;
        int indexOfPiece = Gaming::positionToIndex(pos, __width);
        std::vector<Position> indexToCheck;
        Position temp(0,0);
        int x, y;
        int checkX, checkY;
        if (indexOfPiece < __grid.size() && indexOfPiece >= 0) {
            // Get array of all indexes of surroundings
            int __i = 0;
            int i, k;
            for (i = -1; i <= 1; i++) {
                for (k = -1; k <= 1; k++) {
                    x = pos.x;
                    y = pos.y;
                    checkX = x + i;
                    checkY = y + k;

                    if (__i == 4) {
                        s.array[__i] = PieceType::SELF;
                    } else if (checkX < 0 || checkX >= __height) {
                        s.array[__i] = PieceType::INACCESSIBLE;
                    } else if (checkY < 0 || checkY >= __width) {
                        s.array[__i] = PieceType::INACCESSIBLE;
                    } else {
                        temp.x = checkX;
                        temp.y = checkY;
                        if (__grid[positionToIndex(temp, __width)] != nullptr) {
                            s.array[__i] = __grid[positionToIndex(temp, __width)]->getType();
                        } else {
                            s.array[__i] = PieceType::EMPTY;
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
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

// populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }
        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple --;
            }
        }

        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    unsigned int Game::getNumSimple() const {
        Position temp;
        unsigned int count = 0;
        for (int i = 0; i < __height; i++) {
            for (int k = 0; k < __width; k++) {
                temp.x = i;
                temp.y = k;
                if (__grid[positionToIndex(temp, __width)] != nullptr) {
                    if (__grid[positionToIndex(temp, __width)]->getType() == PieceType::SIMPLE) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    unsigned int Game::getNumAgents() const {
        Position temp;
        unsigned int count = 0;
        for (int i = 0; i < __height; i++) {
            for (int k = 0; k < __width; k++) {
                temp.x = i;
                temp.y = k;
                if (__grid[positionToIndex(temp, __width)] != nullptr) {
                    if (__grid[positionToIndex(temp, __width)]->getType() == PieceType::SIMPLE || __grid[positionToIndex(temp, __width)]->getType() == PieceType::STRATEGIC) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    unsigned int Game::getNumStrategic() const {
        Position temp;
        unsigned int count = 0;
        for (int i = 0; i < __height; i++) {
            for (int k = 0; k < __width; k++) {
                temp.x = i;
                temp.y = k;
                if (__grid[positionToIndex(temp, __width)] != nullptr) {
                    if (__grid[positionToIndex(temp, __width)]->getType() == PieceType::STRATEGIC) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        bool legal = true;
        int checkX, checkY;
        if (pos.x >= __height || pos.x < 0) {
            legal = false;
        } else if (pos.y >= __width || pos.y < 0) {
            legal = false;
        } else {
            checkX = pos.x;
            checkY = pos.y;
            switch (ac) {
                case ActionType::N:
                    checkX--;
                    if (checkX >= __height || checkX < 0) {
                        legal = false;
                    }
                    break;
                case ActionType::NE:
                    checkY++;
                    checkX--;
                    if ((checkY >= __width || checkY < 0) || (checkX >= __height || checkX < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::E:
                    checkY++;
                    if ((checkY >= __width || checkY < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::SE:
                    checkY++;
                    checkX++;
                    if ((checkY >= __width || checkY < 0) || (checkX >= __height || checkX < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::S:
                    checkX++;
                    if ((checkX >= __height || checkX < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::SW:
                    checkY--;
                    checkX++;
                    if ((checkY >= __width || checkY < 0) || (checkX >= __height || checkX < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::W:
                    checkY--;
                    if ((checkY >= __width || checkY < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::NW:
                    checkY--;
                    checkX--;
                    if ((checkY >= __width || checkY < 0) || (checkX >= __height || checkX < 0)) {
                        legal = false;
                    }
                    break;
                case ActionType::STAY:
                    break;
            }
        }
        return legal;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
        Position returnPos;
        returnPos.x = pos.x;
        returnPos.y = pos.y;
            switch (ac) {
                case ActionType::N:
                    returnPos.x--;
                    break;
                case ActionType::NE:
                    returnPos.x--;
                    returnPos.y++;
                    break;
                case ActionType::E:
                    returnPos.y++;
                    break;
                case ActionType::SE:
                    returnPos.y++;
                    returnPos.x++;
                    break;
                case ActionType::S:
                    returnPos.x++;
                    break;
                case ActionType::SW:
                    returnPos.x++;
                    returnPos.y--;
                    break;
                case ActionType::W:
                    returnPos.y--;
                    break;
                case ActionType::NW:
                    returnPos.y--;
                    returnPos.x--;
                    break;
                case ActionType::STAY:
                    break;
            }
        return returnPos;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        int moveX = 1000, moveY = 1000;
        for (int i = -1; i <= 1; i++) {
            for (int k = -1; k <= 1; k++) {
                if ((from.x + i == to.x) && (from.y + k == to.y)) {
                    moveX = i;
                    moveY = k;
                    break;
                }
            }
        }

        if (moveX == 0 && moveY == 0) {
            return ActionType::STAY;
        } else if (moveY == 0) {
            if (moveX == -1) {
                return ActionType::N;
            } else if (moveX == 1) {
                return ActionType::S;
            }
        } else if (moveX == -1 && moveY == -1) {
            return ActionType::NE;
        } else if (moveX == 0 && moveY == -1) {
            return ActionType::W;
        } else if (moveX == 1 && moveY == -1) {
            return ActionType::SW;
        } else if (moveX == -1 && moveY == 1) {
            return ActionType::NE;
        } else if (moveX == 0 && moveY == 1) {
            return ActionType::E;
        } else if (moveX == 1 && moveY == 1) {
            return ActionType::SE;
        }
    }

    unsigned int Game::getNumPieces() const {
        Position temp;
        unsigned int count = 0;
        for (int i = 0; i < __height; i++) {
            for (int k = 0; k < __width; k++) {
                temp.x = i;
                temp.y = k;
                if (__grid[positionToIndex(temp, __width)] != nullptr) {
                    if (__grid[positionToIndex(temp, __width)]->getType() == PieceType::ADVANTAGE || __grid[positionToIndex(temp, __width)]->getType() == PieceType::SIMPLE || __grid[positionToIndex(temp, __width)]->getType() == PieceType::FOOD || __grid[positionToIndex(temp, __width)]->getType() == PieceType::STRATEGIC) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    unsigned int Game::getNumResources() {
        Position temp;
        unsigned int count = 0;
        for (int i = 0; i < __height; i++) {
            for (int k = 0; k < __width; k++) {
                temp.x = i;
                temp.y = k;
                if (__grid[positionToIndex(temp, __width)] != nullptr) {
                    if (__grid[positionToIndex(temp, __width)]->getType() == PieceType::ADVANTAGE || __grid[positionToIndex(temp, __width)]->getType() == PieceType::FOOD) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        Position temp;
        os << "Round " << game.__round << ":\n";
        std::cout << "\nRound " << game.__round << std::endl;
        for (int i = 0; i < game.__height; i++) {
            for (int k = 0; k < game.__width; k++) {
                temp.x = i;
                temp.y = k;
                os << "[";
                std::cout << "[";
                if (game.__grid[positionToIndex(temp, game.__width)] != nullptr) {
                   os << *(game.__grid[positionToIndex(temp, game.__width)]) << std::setw(2) << std::setfill(' ') << "]";
                    std::cout  << *(game.__grid[positionToIndex(temp, game.__width)]) << std::setw(2) << std::setfill(' ') << "]";
                } else {
                    os << std::setw(6) << std::setfill (' ') << "]";
                    std::cout << std::setw(6) << std::setfill (' ') << "]";
                }
            }
            os << "\n";
            std::cout << "\n";
        }
        os << "Status: ";
        switch (game.getStatus()) {
            case Game::Status::PLAYING:
                os << "Playing...\n";
                break;
            case Game::Status::NOT_STARTED:
                os << "Not started...\n";
                break;
            case Game::Status::OVER:
                os << "Over!\n";
                break;
        }
        return os;
    }

    void Game::play(bool verbose) {
        __verbose = verbose;
        __status = Status::PLAYING;
        while (getNumResources() != 0) {
            round();
            if (__verbose && getNumResources() != 0) {
                std::cout << *this;
            }
            __round++;
        }
        __status = Status::OVER;
        if (__verbose) {
            std::cout << *this;
        }
    }

    void Game::round() {
        std::set<Piece *> iset;
        Surroundings s;
        ActionType f;
        Position nextSpot;
        Piece * current, * next;
        Position currentSpot;
        int nextIndex;
        if (__round != 0) {
            for (int i = 0; i < __grid.size(); i++) {
                if (__grid[i] != nullptr && __grid[i]->isViable() && getNumResources() != 0) {
                    current = __grid[i];
                    currentSpot.x = (indexToPosition(i, __width, __height)).x;
                    currentSpot.y = (indexToPosition(i, __width, __height)).y;
                    s = getSurroundings(currentSpot);
                    f = __grid[i]->takeTurn(s);
                    if (isLegal(f, indexToPosition(i, __width, __height))) {
                        nextSpot.x = (move(indexToPosition(i, __width, __height), f)).x;
                        nextSpot.y = (move(indexToPosition(i, __width, __height), f)).y;
                        nextIndex = positionToIndex(nextSpot, __width);
                        next = __grid[nextIndex];
                    }
                    if (next == nullptr) {
                        __grid[positionToIndex(nextSpot, __width)] = current;
                        __grid[i] = nullptr;
                    } else {
                        switch (next->getType()) {
                            case PieceType::SIMPLE:
                                if (next->isViable() && current->getType() != PieceType::SIMPLE) {
                                    (*current) * (*next);
                                    if (current->isViable()) {
                                        delete __grid[nextIndex];
                                        __grid[nextIndex] = current;
                                        __grid[i] = nullptr;
                                    } else if (next->isViable()) {
                                        delete __grid[i];
                                        __grid[i] = nullptr;
                                    } else if (!next->isViable() && !current->isViable()) {
                                        delete __grid[nextIndex];
                                        delete __grid[i];
                                        __grid[nextIndex] = nullptr;
                                        __grid[i] = nullptr;
                                    }
                                }
                                break;
                            case PieceType::STRATEGIC:
                                if (next->isViable()) {
                                    (*current) * (*next);
                                    if (current->isViable()) {
                                        delete __grid[nextIndex];
                                        __grid[nextIndex] = current;
                                        __grid[i] = nullptr;
                                    } else if (next->isViable()) {
                                        delete __grid[i];
                                        __grid[i] = nullptr;
                                    } else if (!next->isViable() && !current->isViable()) {
                                        delete __grid[nextIndex];
                                        delete __grid[i];
                                        __grid[nextIndex] = nullptr;
                                        __grid[i] = nullptr;
                                    }
                                }
                                break;
                            case PieceType::FOOD:
                                if (next->isViable()) {
                                    (*current) * (*next);
                                    delete __grid[nextIndex];
                                    __grid[nextIndex] = current;
                                    __grid[i] = nullptr;

                                }
                                break;
                            case PieceType::ADVANTAGE:
                                if (next->isViable()) {
                                    (*current) * (*next);
                                    delete __grid[nextIndex];
                                    __grid[nextIndex] = current;
                                    __grid[i] = nullptr;
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
}