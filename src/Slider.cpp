//
// Created by pallen on 12/20/2023.
//

#include "azul/Slider.h"

namespace fgcu {

    Slider::Slider() {
        _isHorizontal = true;
        _held = false;
    }

    Slider::Slider(sf::Vector2f size, sf::Vector2f range) {
        _size = size;
        _range = range;

        _held = false;

        if (_size.x > size.y) {
            _isHorizontal = true;
            _knob = sf::CircleShape(_size.y);
            _knob.setOrigin(_size.y, _size.y);
        }
        else {
            _isHorizontal = false;
            _knob = sf::CircleShape(_size.x);
            _knob.setOrigin(_size.x, _size.x);
        }

        _stopMin = sf::CircleShape(_knob.getRadius());
        _stopMin.setOrigin(_stopMin.getRadius(), _stopMin.getRadius());
        _stopMax = sf::CircleShape(_knob.getRadius());
        _stopMax.setOrigin(_stopMax.getRadius(), _stopMax.getRadius());

        if (_isHorizontal) {
            sf::Vector2f maskDim{_knob.getRadius(), _knob.getRadius() * 2.f};
            _maskMin = sf::RectangleShape(maskDim);
            _maskMin.setOrigin({0.f, maskDim.y * 0.5f});
            _maskMax = sf::RectangleShape(maskDim);
            _maskMax.setOrigin({maskDim.x, maskDim.y * 0.5f});
            _barMin = sf::RectangleShape({_knob.getRadius() * 2.f * 0.3f, _knob.getRadius() * 2.f * 0.3f});
            _barMin.setOrigin({0.f, _barMin.getSize().y * 0.5f});
            _barMax = sf::RectangleShape({_knob.getRadius() * 2.f * 0.2f, _knob.getRadius() * 2.f * 0.2f});
            _barMax.setOrigin({0.f, _barMax.getSize().y * 0.5f});
        }
        else {
            sf::Vector2f maskDim{_knob.getRadius() * 2.f, _knob.getRadius()};
            _maskMin = sf::RectangleShape(maskDim);
            _maskMin.setOrigin({maskDim.x * 0.5f, maskDim.y});
            _maskMax = sf::RectangleShape(maskDim);
            _maskMax.setOrigin({maskDim.x * 0.5f, 0.f});
            _barMin = sf::RectangleShape({_knob.getRadius() * 2.f * 0.3f, _knob.getRadius() * 2.f * 0.3f});
            _barMin.setOrigin({_barMin.getSize().x * 0.5f, 0.f});
            _barMax = sf::RectangleShape({_knob.getRadius() * 2.f * 0.2f, _knob.getRadius() * 2.f * 0.2f});
            _barMax.setOrigin({_barMax.getSize().x * 0.5f, 0.f});
        }

        _maskMin.setFillColor(sf::Color::Black);
        _maskMax.setFillColor(sf::Color::Black);

    } // constructor

    void Slider::setPosition(sf::Vector2f position) {
        _position = position;
        if (_isHorizontal) {
            _stopMin.setPosition(position.x, position.y);
            _maskMin.setPosition(position.x, position.y);
            _knob.setPosition(_position.x + _size.x * 0.5f, _position.y);
            _stopMax.setPosition(position.x + _size.x, position.y);
            _maskMax.setPosition(position.x + _size.x, position.y);
        }
        else { // isVertical
            _stopMin.setPosition(position.x, position.y + _size.y);
            _maskMin.setPosition(position.x, position.y + _size.y);
            _knob.setPosition(_position.x, _position.y + _size.y * 0.5f);
            _stopMax.setPosition(position.x, position.y);
            _maskMax.setPosition(position.x, position.y);
        }
        setBars();
    } // setPosition

    void Slider::setColor(sf::Color color) {
        _color = color;
        _stopMin.setFillColor(_color);
        _knob.setFillColor(_color);
        _stopMax.setFillColor(sf::Color(_color.r * 0.5, _color.g * 0.5, _color.b * 0.5));
        _barMin.setFillColor(_stopMin.getFillColor());
        _barMax.setFillColor(_stopMax.getFillColor());
    } // setColor

    void Slider::setBackgroundColor(sf::Color color) {
        _maskMin.setFillColor(color);
        _maskMax.setFillColor(color);
    }

    void Slider::setHeld(bool held) { _held = held; }

    bool Slider::isHeld() { return _held; }

    void Slider::draw(sf::RenderWindow& window) {
        window.draw(_stopMin);
        window.draw(_stopMax);
        window.draw(_maskMin);
        window.draw(_maskMax);
        window.draw(_barMin);
        window.draw(_barMax);
        window.draw(_knob);
    } // draw

    void Slider::moveKnob(sf::Vector2f position) {
        sf::Vector2f knobPos = _knob.getPosition();
        if (_isHorizontal) {
            if(position.x < _stopMin.getPosition().x)
                position = _stopMin.getPosition();
            else if (position.x > _stopMax.getPosition().x)
                position = _stopMax.getPosition();
            _knob.setPosition(position.x, knobPos.y);
        }
        else {
            if(position.y > _stopMin.getPosition().y)
                position = _stopMin.getPosition();
            else if (position.y < _stopMax.getPosition().y)
                position = _stopMax.getPosition();
            _knob.setPosition(knobPos.x, position.y);
        }
        setBars();
    } // moveKNob

    float Slider::getValue() {
        float position = _knob.getPosition().x - _stopMin.getPosition().x;
        float slider =  _stopMax.getPosition().x - _stopMin.getPosition().x;
        float range = _range.y - _range.x;
        if (!_isHorizontal) {
            position = _stopMin.getPosition().y - _knob.getPosition().y;
            slider =  _stopMin.getPosition().y - _stopMax.getPosition().y;
        }
        return position * range / slider;
    } // getValue

    void Slider::setValue(float value) {
        float range = _range.y - _range.x;
        if (_isHorizontal) {
            float slider =  _stopMax.getPosition().x - _stopMin.getPosition().x;
            float position = _stopMin.getPosition().x + value * slider / range;
            _knob.setPosition(position, _knob.getPosition().y);
            moveKnob({_knob.getPosition().x, position});
        }
        else {
            float slider =  _stopMin.getPosition().y - _stopMax.getPosition().y;
            float position = _stopMin.getPosition().y - value * slider / range;
            moveKnob({_knob.getPosition().x, position});
        }
    } //setValue

    bool Slider::contains(sf::Vector2f point) {
        sf::FloatRect bounds = _knob.getLocalBounds();
        sf::Vector2f position = _knob.getPosition();
        sf::Vector2f origin = _knob.getOrigin();
        bounds.left = position.x - origin.x;
        bounds.top = position.y - origin.y;

        return bounds.contains(point);
    } // contains

    bool Slider::checkPressed(sf::Event event) {
        bool pressed = false;

        if (!_held && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // see if mouse is held down the speed slider
                auto mouse = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                _held = contains(mouse);
                pressed = _held;
            } // left mouse button
        } // MouseButtonPressed

        return pressed;
    } // checkPressed

    bool Slider::checkReleased(sf::Event event) {
        bool released = false;

        if (_held && event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                _held = false; // release speed slider
                released = true;
            } // left mouse button
        } // MouseButtonReleased

        return released;
    } // checkReleased

    bool Slider::checkDragged(sf::Event event, sf::RenderWindow& window) {
        bool dragged = false;

        // Azul speed slider
        if (_held && event.type == sf::Event::MouseMoved) {
            auto mouse = sf::Vector2f(sf::Mouse::getPosition(window).x,
                                      sf::Mouse::getPosition(window).y);
            // if mouse held and moved outside of slider knob
            if (!contains(mouse))
                moveKnob(mouse); // move the slider knob
        } // held

        return dragged;
    }  // checkDragged

    void Slider::setBars() {
        if (_isHorizontal) {
            _barMin.setSize({_knob.getPosition().x - _stopMin.getPosition().x, _barMin.getSize().y});
            _barMin.setPosition(_stopMin.getPosition());
            _barMax.setSize({_stopMax.getPosition().x - _knob.getPosition().x, _barMax.getSize().y});
            _barMax.setPosition(_knob.getPosition());
        }
        else {
            _barMin.setSize({_barMin.getSize().x, _stopMin.getPosition().y - _knob.getPosition().y});
            _barMin.setPosition(_knob.getPosition());
            _barMax.setSize({_barMax.getSize().x, _knob.getPosition().y - _stopMax.getPosition().y});
            _barMax.setPosition(_stopMax.getPosition());
        }
    } // setBars

} // fgcu