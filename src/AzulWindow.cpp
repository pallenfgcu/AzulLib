//
// Created by pallen on 6/30/2022.
//

#include "../include/Azul/AzulWindow.h"

namespace fgcu {

    static std::string azul_image = "azul.png";
    static std::string cap_image = "cap.png";


    AzulWindow::AzulWindow() {
        m_title = "";
        m_speed = 0;
        m_start = false;
        m_closing = false;
    }

    AzulWindow::AzulWindow(std::string &title, int width, int height) {
        m_title = title;
        m_speed = SPEED;
        m_window = new fgcu::AnimatedWindow(width, height, m_title);
        m_window->setColor(WINDOW_COLOR);

        m_start = false;
        m_closing = true;
    }

    fgcu::AnimatedWindow* AzulWindow::getWindow() {
        return m_window;
    }

    bool AzulWindow::processInput() {
        sf::Keyboard::Key key = m_window->getLastKey();

        if (!m_start) {
            if (key == sf::Keyboard::Key::S
                || key == sf::Keyboard::Key::Space
                || key == sf::Keyboard::Key::Enter) {
                m_start = true;
            }
        }
        else if (key == sf::Keyboard::Key::X
                 || key == sf::Keyboard::Key::Escape) {
            m_closing = false;
        }
        else {
            if (key == sf::Keyboard::Add
                || key == sf::Keyboard::Equal) {
                m_speed += SPEED_ADJUST;
            } else if (key == sf::Keyboard::Key::Subtract
                    || key == sf::Keyboard::Hyphen) {
                m_speed -= SPEED_ADJUST;
            }
            if (m_speed < MIN_SPEED) {
                m_speed = MIN_SPEED;
            }
            if (m_speed > MAX_SPEED) {
                m_speed = MAX_SPEED;
            }
        }

        return m_closing;
    }

    bool AzulWindow::runFrame() {
        m_closing = m_window->nextFrame();
        return m_closing;
    }

    bool AzulWindow::isStarted() const {
        return m_start;
    }

    bool AzulWindow::isClosing() const {
        return m_closing;
    }

    float AzulWindow::getSpeed() const {
        return m_speed;
    }

    void AzulWindow::setSpeed(float speed) {
        m_speed = speed;
    }

} // fgcu