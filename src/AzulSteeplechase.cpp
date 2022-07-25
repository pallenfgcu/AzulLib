// File: AzulSteeplechase.cpp
//
// Florida Gulf Coast University
// Department of Software Engineering
// Author: P.Allen (pallen@fgcu.edu)
//
// Description: initialize the Azul World with random height
//      walls from the floor up between columns, and place
//      Azul in the bottom left corner facing east.
// --------------------------------------------------------

#include "../include/Azul/AzulSteeplechase.h"
#include <Eagles/Random.h>
#include <string>
#include <iostream>

namespace fgcu {

    AzulSteeplechase::AzulSteeplechase (int rows, int columns) : Azul() {
        std::string title = "Azul Steeple Chase";

        if (rows < 4) {
            std::cout << "Azul's world should have at least 4 rows!" << std::endl;
            rows = 4;
        }

        if (columns < 4) {
            std::cout << "Azul's world should have at least 4 columns!" << std::endl;
            columns = 4;
        }

        m_world = AzulWorld(title, rows, columns);

        // random wall heights from no-wall to 1 below top
        fgcu::Random randomWalls(0, m_world.lastRow() - 1);

        // each column from left to 1 before end on right
        for (int column = m_world.firstColumn(); column < m_world.lastColumn(); column++) {

            // get next random wall height
            int wallHeight = randomWalls.nextInt();

            if (wallHeight) {
                // rows from bottom up
                for (int row = m_world.lastRow(); row >= m_world.fromBottom(wallHeight); row--) {
                    m_world.setAdjacentWalls(row, column, WallType::RightWall);
                }
            }
        }

        // set Azul's starting position
        m_world.setStartPosition(m_world.lastRow(), m_world.firstColumn());

        Azul::init(0);

        // wait for start signal
        while (!m_world.startAnimation()) {
            // display start world
            m_world.runAnimation();
        }
    }

} // fgcu