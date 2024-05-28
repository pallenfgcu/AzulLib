//
// Created by pallen on 11/23/2023.
//
#include <SFML/Graphics.hpp>
#include "AzulBoard.h"
#include "AzulCell.h"
#include <string>

#ifndef AZUL_AZULFILEHANDLER_H
#define AZUL_AZULFILEHANDLER_H

namespace fgcu {

    class AzulFileHandler {
    private:

    public:
        static bool loadFile(const std::string& _fileName, AzulBoard& board);

    private:

    };

}


#endif //AZUL_AZULFILEHANDLER_H
