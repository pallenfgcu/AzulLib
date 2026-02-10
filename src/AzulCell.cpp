//
// Created by pallen on 11/23/2023.
//
#include "../include/azul/AzulCell.h"
#include <string>

namespace fgcu {
    AzulCell::AzulCell() : _walls{0}, _caps{0} { }
    AzulCell::AzulCell(float size, sf::Vector2f position, int row, int column)
        : AzulDrawableCell{size, position, row, column}, _walls{0}, _caps{0} {

    }

    void AzulCell::addWall(AzulUtility::Cardinality wall) {
        _walls |= wall;
        turnOnWall(wall);
    }

    void AzulCell::removeWall(AzulUtility::Cardinality wall) {
        _walls &= ((~(1 << wall)) & 0x000000FF);
    }

    bool AzulCell::hasWall(AzulUtility::Cardinality wall) const {
        return _walls & wall;
    }

    int AzulCell::capCount() const { return _caps; }
    void AzulCell::setCaps(int caps) {
        _caps = caps;
        setCapText(std::to_string(_caps));
        _showCap = _caps > 0;
    }
    void AzulCell::incrementCaps() {
        ++_caps;
        setCapText(std::to_string(_caps));
        _showCap = _caps > 0;
    }
    void AzulCell::decrementCaps() {
        if (_caps > 0)
            --_caps;
        setCapText(std::to_string(_caps));
        _showCap = _caps > 0;
    }
    bool AzulCell::hasCaps() const { return _caps > 0; }


} // fgcu