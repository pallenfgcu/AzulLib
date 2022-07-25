/// File: AzulSteeplechase.h
///
/// Florida Gulf Coast University
/// Department of Software Engineering
/// Author: P.Allen (pallen@fgcu.edu)
///
/// Description: Students show up for graduation and
///     congregate in small groups randomly spaced
///     around outside the arena.  Azul needs to get
///     them lined up into even lines so they
///     can enter the graduation ceremony.
///
///     Azul starts in the bottom left corner facing East.
///     The arena is a fixed size of 8 columns, but may have
///     5 or more rows. The student caps will be placed
///     randomly at the start around the arena with enough
///     caps to fill columns 2 and 5 +/- a few students. Azul
///     is not holding any students when he starts, and he
///     can only place students that he has picked up.
///     Student caps must be placed 1-per cell in vertical
///     columns 2 and 5 starting in row 1, with no gaps. If
///     there is an odd number of students, one of the lines
///      will be shorter than the other by 1 student.  Azul
///     should finish back where he started facing east.
///<pre>
///       -----------------
///     0 |___|.|___|.|___|
///     1 |. . C . . C . .|
///     2 |. . C . . C . .|
///     3 |. . C . . C . .|
///     4 |. . C . . C . .|
///     5 |. . C . . C . .|
///     6 |. . C . . C . .|
///     7 |. . C . . . . .|
///     8 |. . . . . . . .|
///       -----------------
///        0 1 2 3 4 5 6 7
///</pre>
/// --------------------------------------------------------
#include "Azul.h"

#ifndef FGCU_AZULLINES_H
#define FGCU_AZULLINES_H

namespace fgcu {

    class AzulGradLines : public Azul {
    public:
        /// Initialize the Azul World for the Graduation Lines exercise:
        /// \param rows     - number of rows (must be at least 5, default=9)
        /// \param columns  - number of columns (must be 8!)
        explicit AzulGradLines(int rows=9, int columns=8);
    };

} // fgcu

#endif //FGCU_AZULLINES_H
