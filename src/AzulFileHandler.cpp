//
// Created by pallen on 11/23/2023.
//

#include "headers/AzulFileHandler.h"
#include "headers/AzulUtility.h"
#include <fstream>
#include <exception>
#include <algorithm>


namespace fgcu {

    void setVerticalWall(AzulBoard& board, int column, int startRow, int endRow);
    void setHorizontalWall(AzulBoard& board, int row, int startColumn, int endColumn);
    void throwInvalidArgumentEx(int line);

    bool AzulFileHandler::loadFile(const std::string& fileName, AzulBoard& board) {
        bool loaded = false;

        AzulUtility::initRandom();

        std::ifstream dataFile;
        dataFile.open(fileName);
        if (dataFile.is_open()) {

            int line = 1;
            std::string title;
            int rows=0, columns=0;

            while(!dataFile.eof()) {
                std::string name;
                dataFile >> name;

                // process the next item from the data file
                if (AzulUtility::stringCompare(name, "Exercise")) {
                    dataFile >> title;
                }
                else if (AzulUtility::stringCompare(name, "Dimensions")) {
                    dataFile >> rows >> columns;
                }
                else if (AzulUtility::stringCompare(name, "Azul")) {
                    int row=0, column=0;
                    std::string sFace;
                    dataFile >> row >> column >> sFace;
                    board.setStartCell(row, column);
                    board.setStartFacing(AzulUtility::stringToCardinality(sFace));
                }
                else if (AzulUtility::stringCompare(name, "Bag")) {
                    int caps = 0;
                    std::string sCaps;
                    dataFile >> sCaps;
                    if (AzulUtility::stringCompare(sCaps, "Infinity"))
                        board.setStartCaps(-1);
                    else
                        board.setStartCaps(std::stoi(sCaps));
                }
                else if (AzulUtility::stringCompare(name, "Caps")) {
                    if (!board.isInitialized()) {
                        throwInvalidArgumentEx(line);
                    }
                    else {
                        int cellRow=0, cellColumn=0, caps=0;
                        dataFile >> cellRow >> cellColumn >> caps;
                        board.addCellCaps(cellRow, cellColumn, caps);
                    }
                }
                else if (AzulUtility::stringCompare(name, "RandomCaps")) {
                    if (!board.isInitialized()) {
                        throwInvalidArgumentEx(line);
                    }
                    else {
                        int cellRow=0, cellColumn=0, maxCaps=0;
                        dataFile >> cellRow >> cellColumn >> maxCaps;
                        int caps = AzulUtility::getRandomNumber(maxCaps, 1);
                        board.addCellCaps(cellRow, cellColumn, caps);
                    }
                }
                else if (AzulUtility::stringCompare(name, "Wall")) {
                    if (!board.isInitialized()) {
                        throwInvalidArgumentEx(line);
                    }
                    else {
                        int cellRow=0, cellColumn=0;
                        std::string sWall;
                        dataFile >> cellRow >> cellColumn >> sWall;

                        AzulUtility::Cardinality wall = AzulUtility::stringToCardinality(sWall);
                        if (wall == AzulUtility::Cardinality::None)
                            throwInvalidArgumentEx(line);
                        else
                            board.addCellWall(cellRow, cellColumn, wall);
                    }
                }
                else if (AzulUtility::stringCompare(name, "VerticalWall")) {
                    if (!board.isInitialized()) {
                        throwInvalidArgumentEx(line);
                    }
                    else {
                        int startRow, endRow, column;
                        dataFile >> startRow >> column >> endRow;
                        setVerticalWall(board, column, startRow, endRow);
                    }
                }
                else if (AzulUtility::stringCompare(name, "HorizontalWall")) {
                    if (!board.isInitialized()) {
                        throwInvalidArgumentEx(line);
                    }
                    else {
                        int startColumn, endColumn, row=0;
                        dataFile >> row >> startColumn >> endColumn;
                        setHorizontalWall(board, row, startColumn, endColumn);
                    }
                }

                // see if we have enough to initialize the board
                if (!board.isInitialized() && !title.empty() && rows > 0 && columns > 0) {
                    board.init(rows, columns, title);
                    board.setInitialized(true);
                }

                ++line;
            } // not eof

            loaded = true;
        } // file is open

        return loaded;
    } // load file


    void setVerticalWall(AzulBoard& board, int column, int startRow, int endRow) {
        int fromRow=0, toRow=0;

        int maxRows = board.getRows() - 1;

        if (endRow == -1) {
            int rand = AzulUtility::getRandomNumber(maxRows);
            if (rand == 0) {
               return;
            } else {
                if (startRow == maxRows) {
                    endRow = startRow - rand;
                }
                else {
                    endRow = startRow + rand;
                }
            }
        }

        fromRow = std::min(startRow, endRow);
        toRow = std::max(startRow, endRow);

        for (int row=fromRow; row <= toRow; ++row) {
            board.addCellWall(row, column, AzulUtility::Cardinality::East);
        } // each row

    } // setVerticalWall


    void setHorizontalWall(AzulBoard& board, int row, int startColumn, int endColumn) {
        int fromColumn=0, toColumn=0;

        int maxColumns = board.getColumns() - 1;

        if (endColumn == -1) {
            int rand = AzulUtility::getRandomNumber(maxColumns);
            if (rand == 0) {
                return;
            } else {
                if (startColumn == maxColumns) {
                    endColumn = startColumn - rand;
                }
                else {
                    endColumn = startColumn + rand;
                }
            }
        }

        fromColumn = std::min(startColumn, endColumn);
        toColumn = std::max(startColumn, endColumn);

        for (int column=fromColumn; column <= toColumn; ++column) {
            board.addCellWall(row, column, AzulUtility::Cardinality::South);
        } // each row

    } // setHorizontalWall


    void throwInvalidArgumentEx(int line) {
        throw std::invalid_argument("Invalid argument in the file at line " + std::to_string(line));
    }

} // fgcu
