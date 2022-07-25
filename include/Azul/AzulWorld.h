//
// Created by pallen on 7/1/2022.
//

#include "AzulCell.h"
#include "AzulWindow.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <string>

#ifndef FGCU_AZULWORLD_H
#define FGCU_AZULWORLD_H

namespace fgcu {

    struct BorderCells {
        std::vector<AzulCell> rows;
        std::vector<AzulCell> columns;
    };

    typedef unsigned int WallValues;

    class AzulWorld {
    public:
        AzulWorld();

        explicit AzulWorld(std::string &title, int rows=9, int columns=9);

        int getRows() const;

        int getColumns() const;

        int getStartRow() const;
        void setStartRow(int row);

        int getStartColumn() const;
        void setStartColumn(int column);

        void setStartPosition(int row, int column);


        int firstRow() const;
        int lastRow() const;
        int firstColumn() const;
        int lastColumn() const;
        int fromLeft(int offset) const;
        int fromTop(int offset) const;
        int fromRight(int offset) const;
        int fromBottom(int offset) const;

        void setAdjacentWalls(int row, int column, WallValues walls);

        void setCellCaps(int row, int column, int caps);

        AzulCell* getCell(int row, int column);
        AzulCell* getCellAbove(int row, int column);
        AzulCell* getCellLeft(int row, int column);
        AzulCell* getCellRight(int row, int column);
        AzulCell* getCellBelow(int row, int column);


        bool startAnimation() const;
        void addAnimatedShape(AnimatedShape *shape);
        float getAnimationSpeed() const;
        bool runAnimation();

    private:
        void addOuterCellBorders(int row, int column);

        int m_rows;
        int m_columns;
        int m_startRow;
        int m_startColumn;

        AzulWindow m_window;

        //    rows        columns
        std::vector<std::vector<AzulCell>> m_cells;

        BorderCells m_borderCells;
    };

} // fgcu

#endif //FGCU_AZULWORLD_H
