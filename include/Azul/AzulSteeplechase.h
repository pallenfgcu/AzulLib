/// File: AzulSteeplechase.h
///
/// Florida Gulf Coast University
/// Department of Software Engineering
/// Author: P.Allen (pallen@fgcu.edu)
///
/// Description: Exercise using the Azul World to teach
///      basic C++ programming techniques.  This exercise
///      places Azul in the bottom left corner facing east
///      with random height walls between columns.  Azul must
///      climb each wall in front of him and then descend
///      the other side of the wall all the way to the floor
///      and face East before trying to move forward and or
///      climbing the next wall.  Azul is finished when he has
///      reached the bottom right corner and is facing east.
/// --------------------------------------------------------
#include "Azul.h"

#ifndef FGCU_AZULSTEEPLECHASE_H
#define FGCU_AZULSTEEPLECHASE_H

namespace fgcu {

    class AzulSteeplechase : public Azul {
    public:

        ///
        /// Initialize the Azul World for the Steeplechase exercise:
        ///
        ///<pre>
        ///    ---------
        ///  0 |. . . .|     5x4 world (5 rows by 4 columns)
        ///  1 |. .|. .|     Azul starts at: row=4, column=0
        ///  2 |.|.|. .|          finish at: row=4, column=3
        ///  3 |.|.|.|.|
        ///  4 |A|.|.|X|
        ///    ---------
        ///     0 1 2 3
        ///</pre>
        /// Azul will start in the bottom left corner (A) facing East
        /// (to the right), and needs to climb each wall, descending
        /// to the floor on the other side.  He can move forward across
        /// the floor any columns that do not have a wall.  He is finished
        /// when he reaches the bottom right corner (X) facing East.
        ///
        /// \param rows      - number of rows (height of the world)   Default=9
        /// \param columns   - number of columns (width of the world) Default=9
        ///
        explicit AzulSteeplechase (int rows=9, int columns=9);
    };

} // fgcu

#endif //FGCU_AZULSTEEPLECHASE_H
