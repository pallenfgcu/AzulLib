//
// Created by pallen on 12/28/2023.
//
#include <SFML/Graphics.hpp>
#include "azul/RoundedRectangleShape.h"
#include <string>

#ifndef BUTTON_ANIMATEDBUTTON_H
#define BUTTON_ANIMATEDBUTTON_H

namespace fgcu {

    class AnimatedButton : public sf::Drawable {
    public:
        AnimatedButton();
        AnimatedButton(std::string label, sf::Font& font, unsigned int size);

        void setLabel(std::string label);
        void setFont(sf::Font& font);
        void setFontSize(unsigned int size);

        void setColors(sf::Color background, sf::Color border, sf::Color text);

        void setPosition(sf::Vector2f position);

        bool contains(sf::Vector2f point);

        bool isDisabled();
        void setDisabled(bool disable);

        bool isHovered();
        void setHovered(bool hovered);

        bool isClicked();
        void setClicked(bool clicked);

        bool checkHovered(sf::Event event, sf::RenderWindow& window);
        bool checkClicked(sf::Event event);

    private:
        enum State {
            Normal,
            Hovered,
            Clicked,
            Disabled
        };

        struct StateColors{
            sf::Color background;
            sf::Color border;
            sf::Color text;
        };

        sf::RoundedRectangleShape _button;
        std::string _label;
        unsigned int _textSize;
        sf::Text    _text;
        sf::Text    _shadow;

        AnimatedButton::State _state;
        StateColors _normal;
        StateColors _hover;
        StateColors _clicked;
        StateColors _disabled;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateButton();
        void updateColors();
    };

} // fgcu

#endif //BUTTON_ANIMATEDBUTTON_H
