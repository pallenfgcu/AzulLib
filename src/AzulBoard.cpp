//
// Created by pallen on 11/23/2023.
//

#include "azul/AzulBoard.h"

namespace fgcu {


    // public:
    // ------------------------------------------------------------
    AzulBoard::AzulBoard(int rows, int columns, const std::string& title) :
            AzulWindow{rows, columns, title} {
        init(rows, columns, title);
    }

    void AzulBoard::init(int rows, int columns, const std::string& title) {
        AzulWindow::init(rows, columns, title);
        _azulState = AzulState::Starting;
        _startCell  = sf::Vector2i(0, 0);
        _startFacing = fgcu::AzulUtility::Cardinality::None;
        _startCaps = 0;
        _initialized = false;
        _keyStates[sf::Keyboard::KeyCount] = { 0 };
    }

    void AzulBoard::setStartCell(const sf::Vector2i cell) {
        _startCell = cell;
        _azulShape.setPosition(_cells[_startCell.y][_startCell.x].getCellCenter());
    }

    void AzulBoard::setStartCell(const int row, const int column) {
        _startCell = sf::Vector2i(column, row);
        _azulShape.setPosition(_cells[_startCell.y][_startCell.x].getCellCenter());
    }

    void AzulBoard::addCellWall(int row, int column, AzulUtility::Cardinality wall) {
        addCellWall(sf::Vector2i(column, row), wall);
    }

    void AzulBoard::addCellWall(sf::Vector2i location, AzulUtility::Cardinality wall) {
        if (_initialized) {
            _cells[location.y][location.x].addWall(wall);
            switch(wall) {
                case AzulUtility::Cardinality::North:
                    if (location.y > 0) {
                        _cells[location.y - 1][location.x].addWall(AzulUtility::Cardinality::South);
                    }
                    break;
                case AzulUtility::Cardinality::South:
                    if (location.y < _dimensions.y - 1) {
                        _cells[location.y + 1][location.x].addWall(AzulUtility::Cardinality::North);
                    }
                    break;
                case AzulUtility::Cardinality::East:
                    if (location.x < _dimensions.x - 1) {
                        _cells[location.y][location.x + 1].addWall(AzulUtility::Cardinality::West);
                    }
                    break;
                case AzulUtility::Cardinality::West:
                    if (location.x > 0) {
                        _cells[location.y][location.x - 1].addWall(AzulUtility::Cardinality::East);
                    }
            }
        }
    } // addCellWall

    void AzulBoard::addCellCaps(int row, int column, int caps) {
        addCellCaps(sf::Vector2i(column, row), caps);
    }

    void AzulBoard::addCellCaps(sf::Vector2i location, int caps) {
        if (_initialized) {
            _cells[location.y][location.x].setCaps(caps);
        }
    }

    int AzulBoard::cellCapsCount(int row, int column) {
        return cellCapsCount(sf::Vector2i{column, row});
    }

    int AzulBoard::cellCapsCount(sf::Vector2i location) {
        if (_initialized) {
            return _cells[location.y][location.x].capCount();
        }
        return 0;
    }

    void AzulBoard::erase() {
        _title = "Azul's World";
        _dimensions = sf::Vector2i(8, 8);
        _cells.clear();
        _cells.resize(8, std::vector<AzulCell>(8));
        _startCell  = sf::Vector2i(0, 0);
        _startCaps = 0;
        _initialized = false;
    }

    void AzulBoard::startAzul() {
        bool running = true;
        _azulState = AzulState::Starting;
        do {
            running = run();
        } while(running && _azulState == AzulState::Starting);
        _azulStart.setDisabled(true);
    }

    void AzulBoard::stopAzul() {
        bool running = true;
        _azulState = AzulState::Stopped;
        do {
            running = run();
        } while(running && _azulState == AzulState::Stopped);
    }

    bool AzulBoard::run() {
        bool running = true;

        sf::Clock frameTimer;   // frame rate timer
        float lag{0};             // cumulative lag time each frame

        bool done = false;
        while (!done && running) {
            lag = frameTimer.restart().asSeconds();

            running = processEvents(_keyStates);

            if (running) {
                done = update(lag);
            }

            if (running) {
                render(lag);
            }
       } // game loop

        return running;
    }

    void AzulBoard::moveAzul(sf::Vector2i source, sf::Vector2i target, bool collision) {
        if (_azulState != AzulState::Closing) {
            _azulMove.source = _cells[source.y][source.x].getCellCenter();
            _azulMove.target = _cells[target.y][target.x].getCellCenter();

            if (!collision) {
                _azulState = AzulState::Moving;
            }
            else {
                _azulMove.target = _azulMove.source;
                auto sourceBounds = _cells[source.y][source.x].getCellBounds();
                float azulFront = _azulShape.getLocalBounds().width * 0.25f;
                if (target.x < source.x)
                        _azulMove.target.x = sourceBounds.left + azulFront;
                else if (target.x > source.x)
                    _azulMove.target.x = sourceBounds.left + sourceBounds.width - azulFront;
                else if (target.y < source.y)
                    _azulMove.target.y = sourceBounds.top + azulFront;
                else if (target.y > source.y)
                    _azulMove.target.y = sourceBounds.top + sourceBounds.height - azulFront;
                _azulState = AzulState::Colliding;
            }

            // speed is distance converted to milliseconds
            _azulMove.speed.x = (_azulMove.target.x - _azulMove.source.x);
            _azulMove.speed.y = (_azulMove.target.y - _azulMove.source.y);

            _azulMove.animation.image = 0;
            _azulMove.animation.frame = 0;

        }
        run();
    } // moveAzul

    bool AzulBoard::canMove(sf::Vector2i cell, AzulUtility::Cardinality direction) {
        bool move = !hasBorderWall(cell, direction);
        if (move) {
            switch(direction) {
                case AzulUtility::Cardinality::North:
                    if (_cells[cell.y][cell.x].hasWall(AzulUtility::Cardinality::North) ||
                        _cells[cell.y - 1][cell.x].hasWall(AzulUtility::Cardinality::South) ) {
                        move = false;
                    }
                    break;
                case AzulUtility::Cardinality::South:
                    if (_cells[cell.y][cell.x].hasWall(AzulUtility::Cardinality::South) ||
                        _cells[cell.y + 1][cell.x].hasWall(AzulUtility::Cardinality::North) ) {
                        move = false;
                    }
                    break;
                case AzulUtility::Cardinality::East:
                    if (_cells[cell.y][cell.x].hasWall(AzulUtility::Cardinality::East) ||
                        _cells[cell.y][cell.x + 1].hasWall(AzulUtility::Cardinality::West) ) {
                        move = false;
                    }
                    break;
                case AzulUtility::Cardinality::West:
                    if (_cells[cell.y][cell.x].hasWall(AzulUtility::Cardinality::West) ||
                        _cells[cell.y][cell.x - 1].hasWall(AzulUtility::Cardinality::East) ) {
                        move = false;
                    }
                    break;
                default:
                    move = false;
            }
        }
        return move;
    } // canMove

    bool AzulBoard::hasBorderWall(sf::Vector2i cell, AzulUtility::Cardinality direction) {
        bool border = false;
        switch(direction) {
            case AzulUtility::Cardinality::North:
                border = (cell.y == 0);
                break;
            case AzulUtility::Cardinality::South:
                border = (cell.y == _dimensions.y - 1);
                break;
            case AzulUtility::Cardinality::East:
                border = (cell.x == _dimensions.x - 1);
                break;
            case AzulUtility::Cardinality::West:
                border = (cell.x == 0);
        }
        return border;
    }

    void AzulBoard::rotateAzul() {
        if (_azulState != AzulState::Closing) {
            // get current heading
            _azulRotate.source = _azulShape.getRotation();
            // rotate left 90 degrees {modulus = (((a % b) + b) % b)}
            _azulRotate.target = (((_azulRotate.source - 90) % 360) + 360) % 360;
            // calc degrees per millisecond (negative to rotate counter clockwise)
            _azulRotate.speed = -90.f;
            // degrees rotated
            _azulRotate.rotated = 0.f;
            // set state to rotating
            _azulState = AzulState::Rotating;
            // rotate Azul
        }
        run();
    } // rotateAzul

    bool AzulBoard::removeCellCap(sf::Vector2i cell) {
        bool removed = false;
        if (_cells[cell.y][cell.x].hasCaps()) {
            _cells[cell.y][cell.x].decrementCaps();
            removed = true;
        }
        return removed;
    }

    bool AzulBoard::addCellCap(sf::Vector2i cell) {
        bool add = false;
        _cells[cell.y][cell.x].incrementCaps();
        add = true;
        return add;
    }

    bool AzulBoard::cellHasCaps(sf::Vector2i cell) {
        return _cells[cell.y][cell.x].capCount() > 0;
    }

} // fgcu


