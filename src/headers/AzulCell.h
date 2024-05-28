//
// Created by pallen on 11/22/2023.
//
#include "AzulDrawableCell.h"
#include "AzulUtility.h"

#ifndef AZUL_AZULCELL_H
#define AZUL_AZULCELL_H

namespace fgcu {

    class AzulCell : public AzulDrawableCell {
    public:

    private:
        unsigned char _walls;
        int _caps;

    public:
        AzulCell();
        AzulCell(float size_block, sf::Vector2f position, int row, int column);

        void addWall(AzulUtility::Cardinality wall);
        void removeWall(AzulUtility::Cardinality wall);
        [[nodiscard]] bool hasWall(AzulUtility::Cardinality wall) const;
        [[nodiscard]] int capCount() const;
        void setCaps(int caps);
        void incrementCaps();
        void decrementCaps();
        [[nodiscard]] bool hasCaps() const;

    };

}



#endif //AZUL_AZULCELL_H
