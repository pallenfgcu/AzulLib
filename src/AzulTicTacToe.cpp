//
// Created by pallen on 7/16/2022.
//

#include "../include/Azul/AzulTicTacToe.h"
#include <iostream>

namespace fgcu {
    AzulTicTacToe::AzulTicTacToe(int rows, int columns) {
        std::string title = "Azul Tic-Tac-Toe";

        if (rows != 9) {
            std::cout << "Azul's tic-tac-toe board needs to have 9 rows!" << std::endl;
            rows = 9;
        }

        if (columns != 9) {
            std::cout << "Azul's tic-tac-toe board needs to have 9 columns!" << std::endl;
            columns = 9;
        }

        m_world = AzulWorld(title, rows, columns);

        // setup the tic-tac-toe board
        m_world.setAdjacentWalls(0,2,RightWall);
        m_world.setAdjacentWalls(0,5,RightWall);
        m_world.setAdjacentWalls(2,0,BottomWall);
        m_world.setAdjacentWalls(2,2,BottomWall | RightWall);
        m_world.setAdjacentWalls(2,3,BottomWall);
        m_world.setAdjacentWalls(2,5,BottomWall | RightWall);
        m_world.setAdjacentWalls(2,6,BottomWall);
        m_world.setAdjacentWalls(2,8,BottomWall);
        m_world.setAdjacentWalls(3,2,RightWall);
        m_world.setAdjacentWalls(3,5,RightWall);
        m_world.setAdjacentWalls(5,0,BottomWall);
        m_world.setAdjacentWalls(5,2,BottomWall | RightWall);
        m_world.setAdjacentWalls(5,3,BottomWall);
        m_world.setAdjacentWalls(5,5,BottomWall | RightWall);
        m_world.setAdjacentWalls(5,6,BottomWall);
        m_world.setAdjacentWalls(5,8,BottomWall);
        m_world.setAdjacentWalls(6,2,RightWall);
        m_world.setAdjacentWalls(6,5,RightWall);
        m_world.setAdjacentWalls(8,2,RightWall);
        m_world.setAdjacentWalls(8,5,RightWall);

        // set Azul's starting position
        m_world.setStartPosition(4, 4);

        // fixed students
        Azul::init(-1);

        // wait for start signal
        while (!m_world.startAnimation()) {
            // display start world
            m_world.runAnimation();
        }

    } // AzulTicTacToe

} // fgcu