//
// Created by pallen on 7/1/2022.
//
#include <iostream>
#include <string>
#include "../include/Azul/AzulWorld.h"
#include <SFML/Graphics/Rect.hpp>

namespace fgcu {

    static std::string font_file = "RobotoMono-Regular.ttf";

    AzulWorld::AzulWorld() {
        m_rows = 0;
        m_columns = 0;
        m_startRow = 0;
        m_startColumn = 0;
    }

    AzulWorld::AzulWorld(std::string &title, int rows, int columns) {

        m_rows = rows;
        m_columns = columns;

        int cellSize = WINDOW_DEFAULT_SIZE / std::max(m_rows, m_columns);
        int worldWidth = cellSize * m_columns;
        int worldHeight = cellSize * m_rows;

        int windowWidth = worldWidth + 3 * cellSize; // 2 on left, 1 on right
        int windowHeight = worldHeight + 2 * cellSize; // 1 on top, 1 on bottom

        m_window = AzulWindow(title, windowWidth, windowHeight);

        m_startRow = 0;
        m_startColumn = 0;

        m_borderCells.rows.resize(m_rows);
        m_borderCells.columns.resize(m_columns);

        // initialize cells
        sf::Vector2i cellStart = sf::Vector2i(2 * cellSize, cellSize);
        sf::Vector2i cellPosition = cellStart;
        m_cells.resize(rows, std::vector<AzulCell>(columns));
        for (int row = 0; row < rows; row++) {
            cellPosition.x = cellStart.x;
            for (int column = 0; column < columns; column++) {
                m_cells[row][column].setRowColumn(row, column);
                m_cells[row][column].setSize(cellSize);
                m_cells[row][column].setPosition(cellPosition);
                m_cells[row][column].createWalls();
                addOuterCellBorders(row, column);
                m_cells[row][column].createDot();
                m_cells[row][column].createCap();


                sf::Vector2i borderPosition = cellPosition;
                if (column == 0) {
                    borderPosition.x -= cellSize;
                    m_borderCells.rows[row].setRowColumn(row, -1);
                    m_borderCells.rows[row].setSize(cellSize);
                    m_borderCells.rows[row].setPosition(borderPosition);
                    m_borderCells.rows[row].setFillColor(WINDOW_COLOR);
                    borderPosition.x += cellSize;
                }

                if (row == rows - 1) {
                    borderPosition.y += cellSize;
                    m_borderCells.columns[column].setRowColumn(-1, column);
                    m_borderCells.columns[column].setSize(cellSize);
                    m_borderCells.columns[column].setPosition(borderPosition);
                    m_borderCells.columns[column].setFillColor(WINDOW_COLOR);
                }

                cellPosition.x += cellSize;
            }
            cellPosition.y += cellSize;
        }
    }

    int AzulWorld::getRows() const {
        return m_rows;
    }

    int AzulWorld::getColumns() const {
        return m_columns;
    }

    int AzulWorld::getStartRow() const {
        return m_startRow;
    }

    void AzulWorld::setStartRow(int row) {
        m_startRow = row;
    }

    int AzulWorld::getStartColumn() const {
        return m_startColumn;
    }

    void AzulWorld::setStartColumn(int column) {
        m_startColumn = column;
    }

    void AzulWorld::setStartPosition(int row, int column) {
        m_startRow = row;
        m_startColumn = column;
    }

    int AzulWorld::firstRow() const {
        return 0;
    }

    int AzulWorld::lastRow() const {
        if (m_rows)
            return m_rows - 1;
        else
            return 0;
    }

    int AzulWorld::firstColumn() const {
        return 0;
    }

    int AzulWorld::lastColumn() const {
        if(m_columns)
            return m_columns - 1;
        else
            return 0;
    }

    int AzulWorld::fromLeft(int offset) const {
        return firstColumn() + offset;
    }

    int AzulWorld::fromTop(int offset) const {
        return firstRow() + offset;
    }

    int AzulWorld::fromRight(int offset) const {
        return lastColumn() - offset;
    }

    int AzulWorld::fromBottom(int offset) const {
        return lastRow() - offset;
    }
    
    
    void AzulWorld::setAdjacentWalls(int row, int column, WallValues walls) {

        if (walls & WallType::LeftWall) {

            m_cells[row][column].setLeftWall(true);

            // not first column, set right wall on cell to left
            if (column > firstColumn()) {
                m_cells[row][column-1].setRightWall(true);
            }
        }

        if (walls & WallType::TopWall) {

            m_cells[row][column].setTopWall(true);

            // not first row, set bottom wall on cell above
            if (row > firstRow()) {
                m_cells[row-1][column].setBottomWall(true);
            }
        }

        if (walls & WallType::RightWall) {

            m_cells[row][column].setRightWall(true);

            // not last column, set left wall on cell to right
            if (column < lastColumn()) {
                m_cells[row][column+1].setLeftWall(true);
            }
        }

        if (walls & WallType::BottomWall) {

            m_cells[row][column].setBottomWall(true);

            // not last row, set top wall on cell below
            if (row < lastRow()) {
                m_cells[row+1][column].setTopWall(true);
            }
        }

    } // setAdjacentWalls


    void AzulWorld::setCellCaps(int row, int column, int caps) {
        m_cells[row][column].setCaps(caps);
    }


    AzulCell* AzulWorld::getCell(int row, int column) {
        return & m_cells[row][column];
    }

    AzulCell* AzulWorld::getCellAbove(int row, int column) {
        if (row == firstRow()) {
            return nullptr;
        }
        else {
            return getCell(row - 1, column);
        }
    }

    AzulCell* AzulWorld::getCellLeft(int row, int column) {
        if (column == firstColumn()) {
            return nullptr;
        }
        else {
            return getCell(row, column - 1);
        }
    }

    AzulCell* AzulWorld::getCellRight(int row, int column) {
        if (column == lastColumn()) {
            return nullptr;
        }
        else {
            return getCell(row, column + 1);
        }

    }

    AzulCell* AzulWorld::getCellBelow(int row, int column) {
        if (row == lastRow()) {
            return nullptr;
        }
        else {
            return getCell(row + 1, column);
        }
    }


    bool AzulWorld::startAnimation() const {
        return m_window.isStarted();
    }

    void AzulWorld::addAnimatedShape(AnimatedShape *shape) {
        m_window.getWindow()->addShape(shape);
    }

    float AzulWorld::getAnimationSpeed() const {
        return m_window.getSpeed();
    }

    bool AzulWorld::runAnimation() {
        bool running = m_window.processInput();
        if (running) {

            // draw world objects
            // -------------------------------------------

            // draw static objects

            // draw border cells
            for (int row = firstRow(); row <= lastRow(); row++) {
                //std::cout << "row[" << row << "] @ (" << m_borderCells.rows[row].getPosition().x << "," << m_borderCells.rows[row].getPosition().y << ")" << std::endl;
                m_borderCells.rows[row].draw(m_window.getWindow());
                m_borderCells.rows[row].drawCellText(m_window.getWindow(), std::to_string(row), 0.25f);
            }
            for (int column = firstColumn(); column <= lastColumn(); column++) {
                //std::cout << "column[" << column << "] @ (" << m_borderCells.columns[column].getPosition().x << "," << m_borderCells.columns[column].getPosition().y << ")" << std::endl;
                m_borderCells.columns[column].draw(m_window.getWindow());
                m_borderCells.columns[column].drawCellText(m_window.getWindow(), std::to_string(column), 0.25f);
            }

            // draw Azul cells
            for (int row = firstRow(); row <= lastRow(); row++) {
                for (int column = firstColumn(); column <= lastColumn(); column++) {
                    m_cells[row][column].draw(m_window.getWindow());
                }
            }

            // display next frame of animation
            running = m_window.runFrame();
        }
        return running;
    }

    // ----------------------------------------------------
    // private:
    // ----------------------------------------------------

    void AzulWorld::addOuterCellBorders(int row, int column) {
        // add border walls to top and bottom rows
        if (row == firstRow())
            m_cells[row][column].setTopWall(true);
        else if (row == lastRow())
            m_cells[row][column].setBottomWall(true);

        // add border walls to first and last columns
        if (column == firstColumn())
            m_cells[row][column].setLeftWall(true);
        else if (column == lastColumn())
            m_cells[row][column].setRightWall(true);
    }

} // fgcu