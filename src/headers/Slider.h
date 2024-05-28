//
// Created by pallen on 12/20/2023.
//
#include <SFML/Graphics.hpp>

#ifndef SLIDER_SLIDER_H
#define SLIDER_SLIDER_H

namespace fgcu {

    class Slider {

    public:
        Slider();
        Slider(sf::Vector2f size, sf::Vector2f range);
        void setPosition(sf::Vector2f position);
        void setColor(sf::Color color);
        void setBackgroundColor(sf::Color color);

        void setHeld(bool held) ;
        bool isHeld();

        void draw(sf::RenderWindow& window);

        void moveKnob(sf::Vector2f position);

        float getValue();
        void setValue(float value);

        bool contains(sf::Vector2f point);

        bool checkPressed(sf::Event event);
        bool checkReleased(sf::Event event);
        bool checkDragged(sf::Event event, sf::RenderWindow& window);

    private:
        sf::Vector2f _size;
        sf::Vector2f _range;

        sf::Vector2f _position;
        sf::Color _color;
        sf::Color _maskColor;

        sf::CircleShape _knob;
        sf::CircleShape _stopMin;
        sf::CircleShape _stopMax;
        sf::RectangleShape _maskMin;
        sf::RectangleShape _maskMax;
        sf::RectangleShape _barMin;
        sf::RectangleShape _barMax;

        bool _isHorizontal;
        bool _held;

        void setBars();
    };

} // fgcu

#endif //SLIDER_SLIDER_H
