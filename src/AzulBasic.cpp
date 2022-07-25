//
// Created by pallen on 7/7/2022.
//
#include <iostream>
#include "../include/Azul/AzulBasic.h"

namespace fgcu {
    AzulBasic::AzulBasic (int rows, int columns) : Azul() {
        std::string title = "Azul Generic";

        if (rows < 4) {
            std::cout << "Azul's world should have at least 4 rows!" << std::endl;
            rows = 4;
        }

        if (columns < 4) {
            std::cout << "Azul's world should have at least 4 columns!" << std::endl;
            columns = 4;
        }

        m_world = AzulWorld(title, rows, columns);

        // set Azul's starting position
        m_world.setStartPosition(m_world.firstRow(), m_world.firstColumn());

        Azul::init();

        // wait for start signal
        while (!m_world.startAnimation()) {
            // display start world
            m_world.runAnimation();
        }
    }

} // fgcu