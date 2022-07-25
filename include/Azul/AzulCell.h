//
// Created by pallen on 6/26/2022.
//
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Eagles/AnimatedWindow.h>
#include <Eagles/AnimatedCircle.h>
#include <Eagles/AnimatedRectangle.h>

#ifndef FGCU_AZUL_CELL_H
#define FGCU_AZUL_CELL_H

namespace fgcu {

    enum WallType {
        NoWall     = 0,
        LeftWall   = 1,
        TopWall    = 2,
        RightWall  = 4,
        BottomWall = 8
    };

    class AzulCell {


    public:
        AzulCell();
        AzulCell(int row, int column, int size, char walls=WallType::NoWall, int caps=0);

        [[nodiscard]] int getRow() const;
        void setRow(int row);

        [[nodiscard]] int getColumn() const;
        void setColumn(int column);

        void setRowColumn(int row, int column);

        int getSize() const;
        void setSize(int size);

        sf::Vector2i getPosition() const;
        void setPosition(sf::Vector2i position);

        sf::Vector2i getCenter() const;

        [[nodiscard]] bool hasLeftWall() const;
        [[nodiscard]] bool hasRightWall() const;
        [[nodiscard]] bool hasTopWall() const;
        [[nodiscard]] bool hasBottomWall() const;

        void setWalls(char walls);
        void setLeftWall(bool wall);
        void setRightWall(bool wall);
        void setTopWall(bool wall);
        void setBottomWall(bool wall);

        [[nodiscard]] int getCaps() const;
        void setCaps(int caps);
        [[nodiscard]] bool hasCaps() const;
        int incCaps();
        int decCaps();

        unsigned int getCapIndex() const;
        void setCapIndex(unsigned int index);

        void createWalls();
        void createDot();
        void createCap();

        void setFillColor(unsigned int color);

        void draw(AnimatedWindow* window);

        void drawCellText(AnimatedWindow* window, std::string text, float size=1.0);

    private:

        int m_row;
        int m_column;
        int m_size;
        sf::Vector2i m_position;
        char m_walls;
        int m_caps;
        unsigned int m_capIndex;
        sf::Texture m_capImage;
        sf::Font m_font;

        sf::Text m_cellText;


        unsigned int m_color;
        fgcu::AnimatedRectangle m_background;

        fgcu::AnimatedRectangle m_leftWall;
        fgcu::AnimatedRectangle m_topWall;
        fgcu::AnimatedRectangle m_rightWall;
        fgcu::AnimatedRectangle m_bottomWall;
        fgcu::AnimatedRectangle m_cap;
        AnimatedCircle m_dot;
    };

} // fgcu

#endif //FGCU_AZUL_CELL_H
