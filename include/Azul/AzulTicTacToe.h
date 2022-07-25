/// File: AzulSteeplechase.h
///
/// Florida Gulf Coast University
/// Department of Software Engineering
/// Author: P.Allen (pallen@fgcu.edu)
///
/// Description: Azul plays Tic-Tac-Toe
///
///
/// --------------------------------------------------------
#include "Azul.h"

#ifndef FGCU_AZULTICTACTOE_H
#define FGCU_AZULTICTACTOE_H

namespace fgcu {

    class AzulTicTacToe : public Azul {
    public:
        explicit AzulTicTacToe(int rows=9, int columns=9);
    };

} // fgcu

#endif //FGCU_AZULTICTACTOE_H
