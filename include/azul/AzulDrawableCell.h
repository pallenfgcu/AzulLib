//
// Created by pallen on 11/25/2023.
//
#include <SFML/Graphics.hpp>
#include <string>
#include "AzulUtility.h"

#ifndef AZUL_AZULDRAWABLECELL_H
#define AZUL_AZULDRAWABLECELL_H

namespace fgcu {


class AzulDrawableCell : public sf::Drawable {
    protected:
        float _size;
        int _row;
        int _column;
        bool _showCap;

        sf::RectangleShape _block;
        sf::CircleShape _dot;
        sf::RectangleShape _northWall;
        sf::RectangleShape _southWall;
        sf::RectangleShape _eastWall;
        sf::RectangleShape _westWall;
        sf::RectangleShape _capRectangle;
        sf::Sprite _capSprite;
        sf::Text _capText;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        AzulDrawableCell();
        AzulDrawableCell(float size, sf::Vector2f position, int row, int column);

        void setBackground(sf::Color background);

        void setCapTexture(const sf::Texture& capImage);
        void setCapFont(const sf::Font& capFont);
        void setCapText(const std::string& text);

        void turnOnWall(AzulUtility::Cardinality side);
        void turnOffWall(AzulUtility::Cardinality side);

        [[nodiscard]] sf::Vector2f getCellPosition() const;
        [[nodiscard]] sf::Vector2f getCellCenter() const;
        [[nodiscard]] sf::FloatRect getCellBounds() const;
    };


} // fgcu


#endif //AZUL_AZULDRAWABLECELL_H
