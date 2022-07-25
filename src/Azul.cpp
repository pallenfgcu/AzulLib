//
// Created by pallen on 6/25/2022.
//

#include "../include/Azul/Azul.h"
#include <cmath>


namespace fgcu {

    static std::string azul_image = "azul.png";

    Azul::Azul() {
        m_row = 0;
        m_column = 0;
        m_students = 0;
    }

    int Azul::getRow() const {
        return m_row;
    }

    int Azul::getColumn() const {
        return m_column;
    }

    bool Azul::frontIsBlocked() {
        bool blocked = false;

        switch (m_facing) {
            case North:
                blocked = m_world.getCell(m_row, m_column)->hasTopWall();
                break;
            case East:
                blocked = m_world.getCell(m_row, m_column)->hasRightWall();
                break;
            case South:
                blocked = m_world.getCell(m_row, m_column)->hasBottomWall();
                break;
            case West:
                blocked = m_world.getCell(m_row, m_column)->hasLeftWall();
        }

        return blocked;
    }

    void Azul::moveForward() {
        float speedX = 0.0f, speedY = 0.0f;
        sf::Vector2i moveTo;
        int moveRow = m_row;
        int moveColumn = m_column;
        if (!frontIsBlocked()) {
            switch (m_facing) {
                case North:
                    moveRow -= 1;
                    speedY = -1;
                    break;
                case East:
                    moveColumn += 1;
                    speedX = 1;
                    break;
                case South:
                    moveRow += 1;
                    speedY = 1;
                    break;
                case West:
                    moveColumn -= 1;
                    speedX = -1;
            }

            AzulCell* currentCell = m_world.getCell(m_row, m_column);
            sf::Vector2i startFrom = currentCell->getCenter();
            float size = currentCell->getSize();
            float speed = m_world.getAnimationSpeed();
            float distance = 0.0f;
            while (m_world.runAnimation() && distance <= size) {
                m_azul.setHorizontalSpeed(m_world.getAnimationSpeed() * speedX);
                m_azul.setVerticalSpeed(m_world.getAnimationSpeed() * speedY);
                sf::Vector2f current = m_azul.getPosition();
                distance = std::sqrt(std::pow(startFrom.y - current.y, 2) + std::pow(startFrom.x - current.x,2));
            }
            m_azul.setHorizontalSpeed(0.0f);
            m_azul.setVerticalSpeed(0.0f);
            m_row = moveRow;
            m_column = moveColumn;
            currentCell = m_world.getCell(m_row, m_column);
            sf::Vector2i newPosition = currentCell->getCenter();
            m_azul.setPosition(newPosition.x, newPosition.y);
        }
    }

    void Azul::turnLeft() {
        fgcu::Direction newFacing;
        switch (m_facing) {
            case North:
                newFacing = West;
                break;
            case East:
                newFacing = North;
                break;
            case South:
                newFacing = East;
                break;
            case West:
                newFacing = South;
        }
        int origin = static_cast<int>(m_facing);
        if (origin == 0)
            origin = 360;
        int target = static_cast<int>(newFacing);

        while (m_world.runAnimation()) {
            m_azul.setRotationalSpeed(m_world.getAnimationSpeed() * -1.0);

            int heading = m_azul.getRotation();
            if (!(heading >= target && heading <= origin))
                break;
        }
        m_azul.setRotationalSpeed(0.0f);
        m_azul.setRotation(target);
        m_facing = newFacing;
    }

    bool Azul::isFacingEast() {
        return m_facing == East;
    }

    bool Azul::isFacingNorth() {
        return m_facing == North;
    }

    bool Azul::isFacingSouth() {
        return m_facing == South;
    }

    bool Azul::isFacingWest() {
        return m_facing == West;
    }

    bool Azul::currentHasStudents() {
        return m_world.getCell(m_row, m_column)->hasCaps();
    }

    bool Azul::frontHasStudents() {
        bool students = false;

        AzulCell* next = nullptr;

        switch (m_facing) {
            case North:
                next = m_world.getCellAbove(m_row, m_column);
                break;
            case East:
                next = m_world.getCellRight(m_row, m_column);
                break;
            case South:
                next = m_world.getCellBelow(m_row, m_column);
                break;
            case West:
                next = m_world.getCellLeft(m_row, m_column);
        }

        if (next)
            students = next->hasCaps();

        return students;

    }

    void Azul::pickStudent() {
        fgcu::AzulCell* current = m_world.getCell(m_row, m_column);
        if (current->hasCaps()) {
            if (m_students > -1)
                m_students += 1;
            current->decCaps();
        }
    }

    void Azul::putStudent() {
        fgcu::AzulCell* current = m_world.getCell(m_row, m_column);
        if (hasStudents()) {
            if (m_students > 0)
                m_students -= 1;
            current->incCaps();
        }
    }

    bool Azul::hasStudents() {
        return m_students > 0 || m_students == -1;
    }

    unsigned int Azul::getStudentCount() const {
        return m_students;
    }

    bool Azul::isRunning() {
        return m_world.runAnimation();
    }

    // ----------------------------------------------------
    // protected
    // ----------------------------------------------------
    void Azul::init(int students) {
        // get (column,row) start location
        m_row = m_world.getStartRow();
        m_column = m_world.getStartColumn();
        // get cell Azul is starting in
        AzulCell* startCell = m_world.getCell(m_row, m_column);

        m_azulImage.loadFromFile(azul_image);

        // adjust size of azul for cell padding
        float size = startCell->getSize() - 2;
        // shrink Azul a bit for cell padding
        m_azul = fgcu::AnimatedRectangle(size, size);
        // set origin to center
        m_azul.setOrigin(size / 2.0f, size / 2.0f);

        sf::Vector2i startPosition = startCell->getCenter();

        m_azul.setPosition(sf::Vector2f(startPosition.x, startPosition.y));
        m_azul.setTexture(&m_azulImage);
        m_azul.setVisible(true);
        m_facing = fgcu::East;
        m_azul.setRotation(m_facing);

        m_world.addAnimatedShape(&m_azul);

        m_students = students;

    }


} // fgcu