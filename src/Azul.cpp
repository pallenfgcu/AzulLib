//
// Created by pallen on 11/22/2023.
//

#include "../include/Azul.h"
#include "headers/AzulBoard.h"
#include "headers/AzulUtility.h"

namespace fgcu {

    const int INFINITE_CAPS = -1;

    AzulBoard* getImplementation(void* impl) { return reinterpret_cast<AzulBoard*>(impl); }

    bool loadDemo(AzulBoard& board);
    bool loadDefault(AzulBoard& board, int rows=8, int columns = 8);
    bool loadStep(AzulBoard& board, int rows=8, int columns = 8);
    bool loadSteeplechase(AzulBoard& board, int rows=8, int columns = 8);


    Azul::Azul(AzulExercise exercise, int rows, int columns) {

        _board = new AzulBoard();
        
        _currentCell = sf::Vector2i(0, 0);
        _currentFacing = AzulDirection::None;
        _nextFacing = AzulDirection::None;
        _caps = 0;
        _infiniteCaps = false;

        loadExercise(exercise, rows, columns);
    } // constructor

    Azul::~Azul() {
        // AzulBoard does not have a destructor, so it's OK
        // to call free (which does not call class destructor).
        // This will suppress the warning on delete of void*
        free(_board);
    }

    bool Azul::loadExercise(AzulExercise exercise, int rows, int columns) {
        bool loaded {false};

        AzulBoard* theBoard = getImplementation(_board);

        _exercise = exercise;

        switch (_exercise) {
            case AzulExercise::Demo:
                loaded = loadDemo(*theBoard);
                break;
            case AzulExercise::Step:
                loaded = loadStep(*theBoard, rows, columns);
                break;
            case AzulExercise::Steeplechase:
                loaded = loadSteeplechase(*theBoard, rows, columns);
                break;
            default:
                _exercise = AzulExercise::Default;
                loaded = loadDefault(*theBoard, rows, columns);
        } // which exercise

        if (loaded) {
            _currentCell = theBoard->getStartCell();
            _currentFacing = static_cast<AzulDirection>(theBoard->getStartFacing());
            _caps = theBoard->getStartCaps();
            _infiniteCaps = _caps == -1;
            theBoard->startAzul();
        }

        return loaded;
    }   // loadExercise

    bool Azul::isClosing() {
        AzulBoard* theBoard = getImplementation(_board);
        return theBoard->isClosing();
    }

    bool Azul::canMoveForward() {
        AzulBoard* theBoard = getImplementation(_board);
        return theBoard->canMove(_currentCell, static_cast<AzulUtility::Cardinality>(_currentFacing));
    }

    bool Azul::isBorderWall() {
        AzulBoard* theBoard = getImplementation(_board);
        return theBoard->hasBorderWall(_currentCell, static_cast<AzulUtility::Cardinality>(_currentFacing));
    } // isBorderWall

    void Azul::moveForward() {
        AzulBoard* theBoard = getImplementation(_board);
        if (!theBoard->isClosing()) {
            sf::Vector2i nextCell = _currentCell;
            switch(_currentFacing) {
                case AzulDirection::North:
                    nextCell.y -= 1;
                    break;
                case AzulDirection::South:
                    nextCell.y += 1;
                    break;
                case AzulDirection::East:
                    nextCell.x += 1;
                    break;
                case AzulDirection::West:
                    nextCell.x -= 1;
            } // switch

            bool collision = !theBoard->canMove(_currentCell, static_cast<AzulUtility::Cardinality>(_currentFacing));
            theBoard->moveAzul(_currentCell, nextCell, collision);
            if (!collision)
                _currentCell = nextCell;
        }
    } // moveForward

    void Azul::turnLeft() {
        AzulBoard* theBoard = getImplementation(_board);
        if (!theBoard->isClosing()) {
            switch(_currentFacing) {
                case AzulDirection::North:
                    _nextFacing = AzulDirection::West;
                    break;
                case AzulDirection::South:
                    _nextFacing = AzulDirection::East;
                    break;
                case AzulDirection::East:
                    _nextFacing = AzulDirection::North;
                    break;
                case AzulDirection::West:
                    _nextFacing = AzulDirection::South;
            } // switch
            theBoard->rotateAzul();
            _currentFacing = _nextFacing;
        }
    }

    void Azul::stop() {
        AzulBoard* theBoard = getImplementation(_board);
        
        if (!theBoard->isClosing())
            theBoard->stopAzul();
    }

    bool Azul::bagHasCaps() {
        return _infiniteCaps || _caps > 0;
    }

    int Azul::bagCapCount() {
        return _caps;
    }

    bool Azul::canPickupCap() {
        AzulBoard* theBoard = getImplementation(_board);
        return theBoard->cellHasCaps(_currentCell);
    }

    void Azul::pickUpCap() {
        AzulBoard* theBoard = getImplementation(_board);
        if (!theBoard->isClosing()) {
            if (theBoard->cellHasCaps(_currentCell)) {
                theBoard->removeCellCap(_currentCell);
                ++_caps;
            }
        }
    }

    void Azul::putDownCap() {
        AzulBoard* theBoard = getImplementation(_board);
        if (!theBoard->isClosing()) {
            if (bagHasCaps()) {
                theBoard->addCellCap(_currentCell);
                if (_caps > 0)
                    --_caps;
            }
        }
    }

    void Azul::demo() {
        AzulBoard* theBoard = getImplementation(_board);
        if (!theBoard->isClosing()) {
            if (_exercise != AzulExercise::Demo)
                loadExercise(AzulExercise::Demo);

            unsigned short demoCaps[7] = {0x0000, 0x7775, 0x4445, 0x7745, 0x4545, 0x4777, 0x0000};

            bool inverted=false;
            for (int row=0; row<7; ++row ) {
                unsigned short bits = demoCaps[row];
                for (int col=0; col<15; ++col) {
                    int mask = 1 << col;
                    if (!inverted)
                        mask = 1 << (14 - col);
                    if (bits & mask)
                        putDownCap();
                    if (col < 14)
                        moveForward();
                } // columns
                if (row < 6) {
                    turnLeft();
                    if (!inverted) {
                        turnLeft();
                        turnLeft();
                    }
                    moveForward();
                    turnLeft();
                    if (!inverted) {
                        turnLeft();
                        turnLeft();
                    }
                }
                inverted = !inverted;
            } // rows

        }
    } // demo

    bool loadDemo(AzulBoard& board) {
        board.init(7, 15, "Demo");
        board.setInitialized(true);
        board.setStartCell(0, 0);
        board.setStartFacing(AzulUtility::Cardinality::East);
        board.setStartCaps(INFINITE_CAPS);
        return true;
    } // loadDemo

    bool loadDefault(AzulBoard& board, int rows, int columns) {
        board.init(rows, columns, "Azul");
        board.setInitialized(true);
        board.setStartCell(0, 0);
        board.setStartFacing(AzulUtility::Cardinality::East);
        board.setStartCaps(INFINITE_CAPS);
        return true;
    } // loadDemo

    bool loadStep(AzulBoard& board, int rows, int columns) {
        board.init(rows, columns, "Step");
        board.setInitialized(true);
        // setup Azul
        board.setStartCell(rows-1, 0);
        board.setStartFacing(AzulUtility::Cardinality::East);
        board.setStartCaps(0);
        // add walls
        board.addCellWall(rows-1,2,AzulUtility::Cardinality::East);
        for (int column=3; column < columns; ++column) {
            board.addCellWall(rows-2,column,AzulUtility::Cardinality::South);
        }
        // add caps
        board.addCellCaps(rows-2, columns-4, 1);
        return true;
    } // loadStep

    bool loadSteeplechase(AzulBoard& board, int rows, int columns) {
        board.init(rows, columns, "Steeplechase");
        board.setInitialized(true);
        // setup Azul
        board.setStartCell(rows-1, 0);
        board.setStartFacing(AzulUtility::Cardinality::East);
        board.setStartCaps(0);
        // add walls
        AzulUtility::initRandom();
        for (int column=0; column < columns-1; ++column) {
            int height = AzulUtility::getRandomNumber(rows - 1);
            for (int row=rows-1; row > rows-height; --row) {
                board.addCellWall(row,column,AzulUtility::Cardinality::East);
            }
        }
        return true;
    } // loadSteeplechase


} // fgcu

