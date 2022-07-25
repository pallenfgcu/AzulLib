// File: AzulSteeplechase.h
//
// Florida Gulf Coast University
// Department of Software Engineering
// Author: P.Allen (pallen@fgcu.edu)
//
// Description: For exercises using the Azul World to teach
//      basic C++ programming techniques.  This exercise
//      creates a blank world with Azul in the top left
//      corner facing east. Azul has unlimited student caps.
// --------------------------------------------------------
#include "Azul.h"

#ifndef FGCU_AZULBASIC_H
#define FGCU_AZULBASIC_H

namespace fgcu {

    class AzulBasic : public Azul {
    public:
        /**
         * Initialize an empty Azul World with Azul in the
         * top left corner facing east. Azul has unlimited
         * student caps.
         *
         * @param rows
         * @param columns
         */
        explicit AzulBasic(int rows=9, int columns=9);
    };

} // fgcu

#endif //FGCU_AZULBASIC_H
