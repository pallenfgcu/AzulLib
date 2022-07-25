//
// Created by pallen on 7/12/2022.
//

#include "../include/Azul/AzulGradLines.h"
#include <Eagles/Random.h>
#include <string>
#include <iostream>

namespace fgcu {

    AzulGradLines::AzulGradLines(int rows, int columns) : Azul() {
        std::string title = "Azul Steeple Chase";

        if (rows < 5) {
            std::cout << "Azul's arena should have at least 5 rows!" << std::endl;
            rows = 5;
        }

        if (columns != 8) {
            std::cout << "Azul's arena must have 8 columns for this exercise!" << std::endl;
            columns = 8;
        }

        m_world = AzulWorld(title, rows, columns);

        // setup arena
        m_world.setAdjacentWalls(0,0,BottomWall);
        m_world.setAdjacentWalls(0,1,BottomWall | RightWall);
        m_world.setAdjacentWalls(0,3,BottomWall | LeftWall);
        m_world.setAdjacentWalls(0,4,BottomWall | RightWall);
        m_world.setAdjacentWalls(0,6,BottomWall | LeftWall);
        m_world.setAdjacentWalls(0,7,BottomWall);


        // 1st row is entryway to the arena, and there are
        // 2 doors for students to line up on
        int students = (rows - 1) * 2;
        fgcu::Random minus(1, 5, "AzulSub");
        int sub = minus.nextInt();
        students -= sub;

        fgcu::Random randRow(1, rows-1, "AzulRows");
        fgcu::Random randColumn(0, columns-1, "AzulColumns");

        for (int student = students; student > 0; student--) {
            int row = randRow.nextInt();
            int column = randColumn.nextInt();
            int caps = m_world.getCell(row, column)->getCaps();
            m_world.getCell(row, column)->setCaps(caps + 1);
        }

        // set Azul's starting position
        m_world.setStartPosition(m_world.lastRow(), m_world.firstColumn());

        // fixed students
        Azul::init(0);

        // wait for start signal
        while (!m_world.startAnimation()) {
            // display start world
            m_world.runAnimation();
        }

    } // AzulGradLines

} // fgcu