// File: AzulStep.cpp
//
// Florida Gulf Coast University
// Department of Software Engineering
// Author: P.Allen (pallen@fgcu.edu)
//
// Description: initialize the Azul World with a step and
//      one student cap, and place Azul in the bottom
//      left corner facing east.
// --------------------------------------------------------
#include "../include/Azul/AzulStep.h"
#include <iostream>

namespace fgcu {

    AzulStep::AzulStep(int rows, int columns) {
        std::string title = "Azul Steeple Chase";

        if (rows < 4) {
            std::cout << "Azul's world should have at least 4 rows!" << std::endl;
            rows = 4;
        }

        if (columns < 8) {
            std::cout << "The step exercise needs at least 8 columns!" << std::endl;
            columns = 8;
        }


        m_world = AzulWorld(title, rows, columns);

        m_world.setAdjacentWalls(m_world.lastRow(), m_world.fromRight(4), WallType::LeftWall | WallType::TopWall);
        m_world.setAdjacentWalls(m_world.lastRow(), m_world.fromRight(3), WallType::TopWall);
        m_world.setAdjacentWalls(m_world.lastRow(), m_world.fromRight(2), WallType::TopWall);
        m_world.setAdjacentWalls(m_world.lastRow(), m_world.fromRight(1), WallType::TopWall);
        m_world.setAdjacentWalls(m_world.lastRow(), m_world.fromRight(0), WallType::TopWall);

        m_world.setCellCaps(m_world.lastRow(), m_world.fromLeft(1), 1);

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