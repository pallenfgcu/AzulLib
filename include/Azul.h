/// File: Azul.h
///
/// This file represents the public interface for the FGCU mascot Azul, who with limited commands, can
/// be made to navigate in a gridded world with simple obstacles, and can lift and place graduation
/// caps around the board. Different scenarios loaded can offer simple to complex challenges for
/// programming students to overcome.
///
/// Copyright (c) 2024.
/// Authored by: Paul Allen, Instructor II
/// Department of Computing and Software Engineering
/// Florida Gulf Coast University
///
/// This program is free software: you can redistribute it and/or modify it under the terms of the GNU
/// General Public License as published by the Free Software Foundation, either version 3 of the License,
/// or (at your option) any later version. This program is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
/// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a
/// copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
///
/// Contact: pallen@fgcu.edu, www.fgcu.edu/eng
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <string>

#ifndef AZUL_AZUL_H
#define AZUL_AZUL_H

namespace fgcu {
/**
 Class object that provides commands to move Azul around his world.

 Azul is the name of the FGCU Eagle mascot.  Azul lives in a simple world of cells organized in a grid by
 rows and columns. Azul can move one square at a time up, down, left and right within the grid, but must be
 facing the direction he is going to move in as he can only move forward. Azul can only turn left one 90 degree
 turn, so he sometimes needs to do multiple turns to get him facing in the direction he needs to go. Each
 cell can have a wall on any of the four sides that blocks Azul's ability to move in that direction. The outer
 most cells are bordered by magic walls that keep Azul inside his world.

 Azul has a magic bag that can hold an infinite number of graduation caps. He can move around the board
 picking up graduation caps and putting them in his bag, or pulling a cap from his bag and placing it on the
 cell he is standing on. Cells can contain any number of graduation caps, and a small number will display
 in the cap to indicate how many caps are on a single cell.


Demo example:
\verbatim
#include <Azul.h>
int main() {
   Azul azul;    // declare an Azul variable named "azul"
   azul.demo();  // run the demo program
   azul.stop();  // halt Azul so the window will stay open
   return 0;     // exit to the OS
}
\endverbatim

 Note: an Azul variable should not be copied, i.e.:
\verbatim
 Azul another = azul; // do not copy (there can be only one Azul)

 // use a pointer instead
 Azul* pAzul = &azul; // get a pointer to the Azul variable
\endverbatim

 This goes for passing an Azul variable as an argument to a function.  Always pass
 Azul by reference or pointer i.e.:

\verbatim
 void myAzulFunction(Azul& azul) { ... }
\endverbatim
*/
    class Azul {
    private:

        enum AzulDirection {
            None = 0,
            North = 1,
            South = 2,
            East = 4,
            West = 8
        };


        sf::Vector2i _currentCell;
        AzulDirection _currentFacing;
        AzulDirection _nextFacing;
        int _caps;
        bool _infiniteCaps;

        void* _board;

    public:
        /// Constructs a new instance of Azul
        /// \param exercise name of the data-file for the exercise to load
        /// \see loadExercise()
        explicit Azul(std::string exercise={});

        ~Azul();

        /// Loads a data file for an exercise that configures things like the
        /// number of rows and columns in the grid, walls, caps, starting position, etc.
        /// \param exerciseFile name of the data-file for the exercise to load
        /// \return true if the exercise file was successfully loaded
        bool loadExercise(std::string exerciseFile);

        /// Determine if Azul can move one cell forward from his current cell in the
        /// direction he is currently facing.
        /// \return false if a wall blocks his way or he is facing a border wall, true otherwise
        bool canMoveForward();

        /// Determine if Azul is in a border cell and is facing a border wall
        /// \return true if he is in a cell on the edge of the board and facing an outside wall
        bool isBorderWall();

        /// Move Azul forward one cell in the direction he is facing. Does nothing if he is blocked.
        void moveForward();

        /// Make Azul face 90 degrees left of his current direction, i.e. North becomes West, West becomes
        /// South, South becomes East, and East becomes North.
        void turnLeft();

        /// Make Azul stop in his current location and stay there indefinitely, or until another movement
        /// command is given. This should be the last command given in a program to keep Azul's world from
        /// closing when a challenge has been completed.
        void stop();

        /// Determine if Azul is currently carrying any graduation caps in Azul's magic cap bag.
        /// \return true if he has one more caps, or infinite caps
        bool bagHasCaps();

        /// Get the current number of graduation caps in Azul's magic cap bag.
        /// \return number of graduation caps (0=none, -1=inifinite)
        int bagCapCount();

        /// Determine if there is one or more graduation caps at the current cell that Azul is standing on.
        /// \return true if the current cell has one or more graduation caps
        bool canPickupCap();

        /// Azul picks up a graduation cap from the current cell he is standing on and places it in his magic cap bag.
        void pickUpCap();

        /// Azul takes a graduation cap from his magic cap bag and places it an the current cell he is standing on.
        /// This will not do anything if Azul's magic cap bag is empty.
        void putDownCap();

        /// Run a program that demonstrates Azul's ability to navigate his world and drop graduation caps.
        /// Make sure the exercise file "demo.dat" has been placed in your projects cmake_build_debug folder.
        /// \param demoFile - optional path/demo.dat to locate the file outside of the project directory
        void demo(std::string demoFile={});
    };


}



#endif //AZUL_AZUL_H
