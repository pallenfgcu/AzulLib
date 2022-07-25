//
// Created by pallen on 6/26/2022.
//

#include "../include/Azul/AzulCell.h"
#include <string>

namespace fgcu {

    static std::string cap_image = "cap.png";
    static std::string font_file = "RobotoMono-Regular.ttf";

    AzulCell::AzulCell() {
        m_row = 0;
        m_column = 0;
        m_size = 0;
        m_walls = WallType::NoWall;
        m_caps = 0;
        m_capImage.loadFromFile(cap_image);
        m_font.loadFromFile(font_file);
        m_capIndex = -1;
        m_background.setVisible(false);
    }

    AzulCell::AzulCell(int row, int column, int size, char walls, int caps) {
        m_row = row;
        m_column = column;
        m_size = size;
        m_walls = walls;
        m_caps = caps;
        m_capImage.loadFromFile(cap_image);
        m_font.loadFromFile(font_file);
        m_capIndex = -1;
    }


    int AzulCell::getRow() const {
        return m_row;
    }

    void AzulCell::setRow(int row) {
        m_row = row;
    }

    int AzulCell::getColumn() const {
        return m_column;
    }

    void AzulCell::setColumn(int column) {
        m_column = column;
    }

    void AzulCell::setRowColumn(int row, int column) {
        m_row = row;
        m_column = column;
    }


    int AzulCell::getSize() const {
        return m_size;
    }

    void AzulCell::setSize(int size) {
        m_size = size;
    }

    sf::Vector2i AzulCell::getPosition() const {
        return m_position;
    }

    void AzulCell::setPosition(sf::Vector2i position) {
        m_position = position;
    }

    sf::Vector2i AzulCell::getCenter() const {
        sf::Vector2i position = m_position;
        // add 1/2 size to top-left
        position.x += m_size / 2;
        position.y += m_size / 2;
        return position;
    }

    bool AzulCell::hasLeftWall() const {
        return m_walls & WallType::LeftWall;
    }

    bool AzulCell::hasRightWall() const {
        return m_walls & WallType::RightWall;
    }

    bool AzulCell::hasTopWall() const {
        return m_walls & WallType::TopWall;
    }

    bool AzulCell::hasBottomWall() const {
        return m_walls & WallType::BottomWall;
    }

    void AzulCell::setWalls(char walls) {
        m_walls = walls;
        m_leftWall.setVisible(hasLeftWall());
        m_rightWall.setVisible(hasRightWall());
        m_topWall.setVisible(hasTopWall());
        m_bottomWall.setVisible(hasBottomWall());
    }

    void AzulCell::setLeftWall(bool wall) {
        if (wall)
            m_walls |= WallType::LeftWall;
        else
            m_walls &= ~static_cast<char>(WallType::LeftWall);
        m_leftWall.setVisible(hasLeftWall());
    }

    void AzulCell::setRightWall(bool wall) {
        if (wall)
            m_walls |= WallType::RightWall;
        else
            m_walls &= ~static_cast<char>(WallType::RightWall);
        m_rightWall.setVisible(hasRightWall());
    }

    void AzulCell::setTopWall(bool wall) {
        if (wall)
            m_walls |= WallType::TopWall;
        else
            m_walls &= ~static_cast<char>(WallType::TopWall);
        m_topWall.setVisible(hasTopWall());
    }

    void AzulCell::setBottomWall(bool wall) {
        if (wall)
            m_walls |= WallType::BottomWall;
        else
            m_walls &= ~static_cast<char>(WallType::BottomWall);
        m_bottomWall.setVisible(hasBottomWall());
    }


    int AzulCell::getCaps() const {
        return m_caps;
    }

    void AzulCell::setCaps(int caps) {
        m_caps = caps;
        m_cellText.setString(std::to_string(m_caps));
    }

    bool AzulCell::hasCaps() const {
        return m_caps > 0;
    }

    int AzulCell::incCaps() {
        m_caps += 1;
        m_cap.setVisible(true);
        m_cellText.setString(std::to_string(m_caps));
        return m_caps;
    }

    int AzulCell::decCaps() {
        if (m_caps > 0)
            m_caps -= 1;
        if (!m_caps)
            m_cap.setVisible(false);
        m_cellText.setString(std::to_string(m_caps));
        return m_caps;
    }

    unsigned int AzulCell::getCapIndex() const {
        return m_capIndex;
    }

    void AzulCell::setCapIndex(unsigned int index) {
        m_capIndex = index;
    }

    const int WALL_SIZE = 2;
    const unsigned int WALL_COLOR = 0xD3D3D3FF; // LightGray

    void AzulCell::createWalls() {
        
        m_leftWall = fgcu::AnimatedRectangle(WALL_SIZE, m_size);
        m_leftWall.setFillColor(sf::Color(WALL_COLOR));
        m_leftWall.setPosition(m_position.x, m_position.y);
        m_leftWall.setVisible(hasLeftWall());

        m_topWall = fgcu::AnimatedRectangle(m_size, WALL_SIZE);
        m_topWall.setFillColor(sf::Color(WALL_COLOR));
        m_topWall.setPosition(m_position.x, m_position.y);
        m_topWall.setVisible(hasTopWall());

        m_rightWall = fgcu::AnimatedRectangle(WALL_SIZE, m_size);
        m_rightWall.setFillColor(sf::Color(WALL_COLOR));
        m_rightWall.setPosition(m_position.x + m_size - WALL_SIZE, m_position.y);
        m_rightWall.setVisible(hasRightWall());

        m_bottomWall = fgcu::AnimatedRectangle(m_size, WALL_SIZE);
        m_bottomWall.setFillColor(sf::Color(WALL_COLOR));
        m_bottomWall.setPosition(m_position.x, m_position.y + m_size - WALL_SIZE);
        m_bottomWall.setVisible(hasBottomWall());
    }


    void AzulCell::createDot() {
        sf::Vector2i position = getCenter();

        m_dot = fgcu::AnimatedCircle(4);
        m_dot.setFillColor(sf::Color(WALL_COLOR));
        m_dot.setOrigin(4, 4);
        m_dot.setPosition(position.x, position.y);
    }

    void AzulCell::createCap() {
        sf::Vector2i position = getCenter();

        m_cap = fgcu::AnimatedRectangle(m_size, m_size);
        m_cap.setOrigin(m_size / 2.0f, m_size / 2.0f);
        m_cap.setPosition(position.x, position.y);
        m_cap.setTexture(&m_capImage);
        m_cap.setVisible(hasCaps());
    }


    void AzulCell::setFillColor(unsigned int color) {
        m_color = color;
        m_background = fgcu::AnimatedRectangle(m_size, m_size);
        m_background.setFillColor(sf::Color(color));
        m_background.setPosition(m_position.x, m_position.y);
        m_background.setVisible(true);
    }

    void AzulCell::draw(AnimatedWindow* window) {
        if (m_background.isVisible())
            window->draw(m_background);

        if (m_leftWall.isVisible())
            window->draw(m_leftWall);

        if (m_topWall.isVisible())
            window->draw(m_topWall);

        if (m_rightWall.isVisible())
            window->draw(m_rightWall);

        if (m_bottomWall.isVisible())
            window->draw(m_bottomWall);

        window->draw(m_dot);

        if (hasCaps()) {
            window->draw(m_cap);
            drawCellText(window, std::to_string(m_caps), 0.2f);
        }
    }


    // ----------------------------------------------------
    // private:
    // ----------------------------------------------------

    void AzulCell::drawCellText(AnimatedWindow* window, std::string text, float size) {
        float fontSize = float(m_size) * size;
        m_cellText.setFont(m_font);
        m_cellText.setString(text);
        m_cellText.setCharacterSize(fontSize); // in pixels
        sf::FloatRect textRect = m_cellText.getLocalBounds();
        m_cellText.setOrigin(textRect.left + textRect.width / 2.0f,
                             textRect.top + textRect.height / 2.0f);
        sf::Vector2i position = getCenter();
        m_cellText.setPosition(position.x, position.y);
        m_cellText.setFillColor(sf::Color::Black);
        m_cellText.setStyle(sf::Text::Bold);
        window->draw(m_cellText);
    }

} // fgcu