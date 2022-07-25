// File: AzulStep.h
//
// Florida Gulf Coast University
// Department of Software Engineering
// Author: P.Allen (pallen@fgcu.edu)
//
// Description: Exercise using the Azul World to teach
//      basic C++ programming techniques.  This exercise
//      places Azul in the bottom left corner facing east
//      with a one-row high step at the bottom across the
//      last 5 columns.  A student cap exists in front of
//      Azul, and he needs to pick the cap up and while
//      moving east along the floor, climb the step, place
//      the student cap on the second column on top of the
//      step, and then finish in the last column on top of
//      the step.
// --------------------------------------------------------

#include "Azul.h"

#ifndef FGCU_AZULSTEP_H
#define FGCU_AZULSTEP_H

namespace fgcu {

    class AzulStep : public Azul {
    public:

        /**
         * Initialize the Azul World for the Steeplechase exercise:
         *
         *    -------------------
         *  0 |. . . . . . . . .|     5x8 world (5 rows by 8 columns)
         *  1 |. . . . . . . . .|     Azul starts at: row=4, column=0
         *  2 |. . . . . . . . .|          finish at: row=3, column=8
         *  3 |. . . . . S . . X|
         *  4 |A C . .|---------|
         *    -------------------
         *     0 1 2 3 4 5 6 7 8
         *
         * Azul will start in the bottom left corner (A) facing East
         * (to the right), with a student cap (C) in the next spot. Azul
         * should move forward one column and pick up the student cap,
         * and then continue moving forward until forward is blocked. Azul
         * should then climb the step to be facing East, move forward to
         * the second column on top of the step and place the student cap (S).
         * Then move to the last column on top of the step and finish facing
         * East (X).
         *
         * @param rows      - number of rows (height of the world)   Default=9
         * @param columns   - number of columns (width of the world) Default=9
         */
        explicit AzulStep(int rows=9, int columns=9);
    };

} // fgcu

#endif //FGCU_AZULSTEP_H
