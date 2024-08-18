//
// Created by pallen on 11/22/2023.
//
#include <SFML/Graphics.hpp>
#include "AzulCell.h"
#include "AzulWindow.h"
#include "AzulUtility.h"
#include <string>
#include <vector>

#ifndef AZUL_AZULBOARD_H
#define AZUL_AZULBOARD_H


namespace fgcu {


    class AzulBoard : public AzulWindow {
    private:

        // Azul starting properties
        sf::Vector2i _startCell;
        fgcu::AzulUtility::Cardinality _startFacing;
        int _startCaps;

        // keyboard state handling
        AzulUtility::KeyPressedState _keyStates[sf::Keyboard::KeyCount];

        bool _initialized;

    public:
        explicit AzulBoard(int rows=8, int columns=8, const std::string& title="Azul's World");

        void init(int rows, int columns, const std::string& title) override;

        [[nodiscard]] std::string getTitle() const { return _title; }
        [[nodiscard]] int getRows() const { return _dimensions.y; }
        [[nodiscard]] int getColumns() const { return _dimensions.x; }

        [[nodiscard]] sf::Vector2i getStartCell() const { return _startCell; }
        void setStartCell(const sf::Vector2i cell);
        void setStartCell(const int row, const int column);

        [[nodiscard]] fgcu::AzulUtility::Cardinality getStartFacing() const { return _startFacing; }
        void setStartFacing(const fgcu::AzulUtility::Cardinality face) { _startFacing = face; }

        [[nodiscard]] int getStartCaps() const { return _startCaps; }
        void setStartCaps(const int caps) { _startCaps = caps; }

        [[nodiscard]] bool isInitialized() const { return _initialized; }
        void setInitialized(const bool initialized) { _initialized = initialized; }

        void addCellWall(int row, int column, AzulUtility::Cardinality wall);
        void addCellWall(sf::Vector2i location, AzulUtility::Cardinality wall);
        void addCellCaps(int row, int column, int caps);
        void addCellCaps(sf::Vector2i location, int caps);
        int cellCapsCount(sf::Vector2i location);

        void erase();

        void startAzul();
        void stopAzul();
        bool run();
        void moveAzul(sf::Vector2i source, sf::Vector2i target, bool collision=false);
        bool canMove(sf::Vector2i cell, AzulUtility::Cardinality direction);
        bool hasBorderWall(sf::Vector2i cell, AzulUtility::Cardinality direction);
        void rotateAzul();
        bool removeCellCap(sf::Vector2i cell);
        bool addCellCap(sf::Vector2i cell);
        bool cellHasCaps(sf::Vector2i cell);


    private:

    };


}



#endif //AZUL_AZULBOARD_H
