//
// Created by pallen on 11/22/2023.
//

#include "../include/Azul.h"
#include "headers/AzulBoard.h"
#include "headers/AzulUtility.h"
#include "headers/AzulFileHandler.h"

namespace fgcu {

    AzulBoard* getImplementation(void* impl) { return reinterpret_cast<AzulBoard*>(impl); }

    Azul::Azul(std::string exercise) {

        _board = new AzulBoard();
        
        _currentCell = sf::Vector2i(0, 0);
        _currentFacing = AzulDirection::None;
        _nextFacing = AzulDirection::None;
        _caps = 0;
        _infiniteCaps = false;

        if (!exercise.empty())
            loadExercise(exercise);
    } // constructor

    Azul::~Azul() {
        // AzulBoard does not have a destructor, so it's OK
        // to call free (which does not call class destructor).
        // This will suppress the warning on delete of void*
        free(_board);
    }
    
    bool Azul::loadExercise(std::string exerciseFile) {
        bool load = false;
        AzulBoard* theBoard = getImplementation(_board);
        
        if (!theBoard->isClosing()) {
            theBoard->erase();
            load = AzulFileHandler::loadFile(exerciseFile, *theBoard);
            if (load) {
                _currentCell = theBoard->getStartCell();
                _currentFacing = static_cast<AzulDirection>(theBoard->getStartFacing());
                _caps = theBoard->getStartCaps();
                _infiniteCaps = _caps == -1;
                theBoard->startAzul();
            }
        }
        return load;
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

    void Azul::demo(std::string demoFile) {
        AzulBoard* theBoard = getImplementation(_board);
        if (!theBoard->isClosing()) {

            if (demoFile.empty()) {
                loadExercise("demo.dat");
            }
            else {
                loadExercise(demoFile);
            }

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

} // fgcu

