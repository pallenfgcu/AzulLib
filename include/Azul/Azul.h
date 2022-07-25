/**
 * file: Azul.h
 *
 * Florida Gulf Coast University
 * Department of Software Engineering
 *
 * Author: P.Allen (pallen@fgcu.edu)
 *
 * This is a base class for Azul, the mascot of FGCU. Azul is a
 * simple animated character in a world of cells laid out in rows
 * and columns.  Each cell can have one or more of its walls on
 * which blocks Azul from moving in that direction to the next cell.
 * Azul can follow basic command to move from cell to cell, turn to
 * face another cell, and to determine if his current direction is blocked.
 * There are student graduation caps that can appear in a cell to
 * indicate 1 or more students are present in that cell (a number is
 * displayed inside the cap to indicate how many students are present).
 * Azul can pick up students from the current cell he is standing on
 * if any are present, or can put down 1 student at a time in the
 * current cell.
 *
 * This class MUST be derived by an implementing class that configures
 * the starting state of Azul's world and calls the protected function
 * init() to setup Azul and get the world up and running.  The init()
 * function blocks on a "start" flag that must be set by the user pressing
 * a start key on the keyboard. This will return control to the derived class's
 * function that called init().
 *
 * Azul is based on Karel in the online Stanford Engineering Everywhere course
 * by Standford University (https://see.stanford.edu/course/cs106a).
 */

#include <Eagles/AnimatedWindow.h>
#include <Eagles/AnimatedRectangle.h>
#include <SFML/Graphics/Texture.hpp>
#include "AzulWorld.h"
#include <string>
#include <vector>

#ifndef FGCU_AZUL_H
#define FGCU_AZUL_H

namespace fgcu {

    enum Direction {
        Unknown =  -1,
        North   =   0,
        East    =  90,
        South   = 180,
        West    = 270
    };


    class Azul {
    public:
        /**
         * Default constructor - create a blank Azul world
         *  with no title, zero rows and columns.  Should
         *  only be used to declare an Azul type variable,
         *  and then call a property constructor.
         */
        Azul();

        /**
         * Constructor - a property constructor that initializes
         *  an Azul world that is rows x columns cells large.
         * @param title     - window title
         * @param rows      - number of rows (0 <-> rows - 1)
         * @param columns   - number of columns (0 <-> columns - 1)
         */
        Azul(std::string title, int rows, int columns);


        /**
         * Get the row number of the cell that Azul is currently in.
         * @return int - row number
         */
        [[nodiscard]] int getRow() const;

        /**
         * Get the column number of the cell that Azul is currently in.
         * @return int - column number
         */
        [[nodiscard]] int getColumn() const;

        /**
         * Check to see if there is a wall on the side of the current cell
         * that Azul is facing, e.g.: if Azul is facing East, does the current
         * cell have a wall on its right side.
         * @return bool - true if wall exists
         */
        bool frontIsBlocked();

        /**
         * Move Azul to the next cell in the direction he is facing, e.g.: if Azul
         * is facing North, then move to cell row - 1 and same column. Function will
         * do nothing if Azul is blocked in the direction he is facing.
         */
        void moveForward();

        /**
         * Rotate Azul 90 degrees to the left of his current direction, e.g.: if Azul is
         * facing East, he will be facing North after 1 call to turnLeft. Subsequent calls
         * would rotate through West, South, and then East again.
         */
        void turnLeft();

        /**
         * Check to see if Azul is currently facing East.
         * @return bool - true if facing East
         */
        bool isFacingEast();

        /**
         * Check to see if Azul is currently facing North.
         * @return bool - true if facing North
         */
        bool isFacingNorth();

        /**
         * Check to see if Azul is currently facing South.
         * @return bool - true if facing South
         */
        bool isFacingSouth();

        /**
         * Check to see if Azul is currently facing West.
         * @return bool - true if facing West
         */
        bool isFacingWest();

        /**
         * Check to see if the cell that Azul is currently in
         * has 1 or more students (graduation cap) present.
         * @return bool - true if students present
         */
        bool currentHasStudents();

        /**
         * Check to see if Azul if the cell in front of Azul's
         * current cell has 1 or more students (graduation cap)
         * present, e.g. if facing West, does the cell in Row - 1
         * and same column have a student cap showing with 1 or
         * or more students.  Will return false if facing a border
         * wall, but can look over a wall and see if students are
         * present.
         * @return bool - true if students present
         */
        bool frontHasStudents();

        /**
         * Pick up 1 student from the current cell that Azul is standing
         * on. This will increase the number of students in Azul's bag
         * (Azul can carry an infinite number of students), and will
         * decrease the number of student caps present on the current cell.
         * The cap icon will disappear when Azul picks up the last student
         * in a cell. This function will do nothing if no students are present
         * in the current cell.
         */
        void pickStudent();

        /**
         * Put 1 student from Azul's bag onto the current cell that Azul is
         * standing on. This will decrease the number of students in Azul's bag
         * by 1 (unless Azul has been set with infinite students in his bag).
         * This increases the number of student caps present on the current cell.
         * The cap icon will appear if Azul is putting down the first student on
         * the cell. This function will do nothing if no students are present
         * in Azul's bag, unless Azul has been configured to hold infinite students.
         */
        void putStudent();

        /**
         * Check to see if Azul has any students in his bag. This will return true
         * if Azul is carrying at least 1 student, or if he has been configured to
         * have infinite students.
         * @return bool - true if Azul has students available in his bag
         */
        bool hasStudents();

        /**
         * Returns the number of students Azul is carrying in his bag.
         * @return int - number of students in Azul's bag (-1 means infinite students available)
         */
        unsigned int getStudentCount() const;

        /**
         * Checks to see if Azul's world is running, i.e. the window close event has not been
         * triggered.  This function also runs any current animation and displays the current
         * state of Azul's world.  This function should be called in a loop to keep the window
         * up and displayed.
         * @return bool - true if the world is not closing
         */
        bool isRunning();

    protected:

        /**
         * Initialize Azul's world based on configuration set by classes that derive from Azul
         * @param students - number of students Azul starts out carrying.  A zero (0) value means
         * Azul current does not have any students, and is limited to only carrying the amount of
         * student caps present in the world at configuration time.  A -1 value will set Azul to
         * infinite mode where he as an infinite number of students available in his bag.
         *
         * This function will block on the "start" flag in Azul's world. Pressing one of the start
         * keys (Spacebar, Enter key, or 'S' key) will cause the function to return to the caller.
         */
        void init(int students=-1);

        AzulWorld m_world;          // The grid of rows x column cells with walls and caps

        int m_row;                  // The row number of the cell that Azul is currently in
        int m_column;               // The column number of the cell that Azul is currently in
        fgcu::Direction m_facing;   // The direction that Azul is currently facing

        AnimatedRectangle m_azul;   // The graphic shape of Azul
        sf::Texture m_azulImage;    // The image of Azul that is displayed on his rectangle

        int m_students;             // The number of students in Azul's bag (-1 means infinite)

    };

} // fgcu

#endif //FGCU_AZUL_H
