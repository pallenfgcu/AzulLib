//
// Created by pallen on 6/30/2022.
//
#include <Eagles/AnimatedWindow.h>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

#ifndef FGCU_AZULWINDOW_H
#define FGCU_AZULWINDOW_H

namespace fgcu {

    const float WINDOW_DEFAULT_SIZE = 800.0;
    const unsigned int BORDER_COLOR = 0xD3D3D3FF; // LightGray
    const unsigned int WALL_COLOR = 0x808080FF;   // Gray
    const unsigned int WINDOW_COLOR = 0xE0FFFFFF; // LightCyan

    const float SPEED = 100;
    const float SPEED_ADJUST = 50;
    const float MIN_SPEED = 50;
    const float MAX_SPEED = 10000;

    class AzulWindow {
    public:
        AzulWindow();
        AzulWindow(std::string &title, int width, int height);

        fgcu::AnimatedWindow* getWindow();

        bool processInput();
        bool runFrame();

        bool isStarted() const;
        bool isClosing() const;

        float getSpeed() const;
        void setSpeed(float speed);

    private:
        fgcu::AnimatedWindow* m_window;
        std::string m_title;

        float m_speed;
        bool m_start;
        bool m_closing;
    };

} // fgcu

#endif //FGCU_AZULWINDOW_H
