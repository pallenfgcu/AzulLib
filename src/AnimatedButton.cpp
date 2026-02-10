//
// Created by pallen on 12/28/2023.
//

#include <cmath>

#include "azul/AnimatedButton.h"
#include "azul/AzulUtility.h"

namespace fgcu {

    AnimatedButton::AnimatedButton() {
        _state = Normal;
        _textSize = 0;
    }

    AnimatedButton::AnimatedButton(std::string label, sf::Font &font, unsigned int size) {
        _state = Normal;
        _label = label;
        _textSize = size;

        _text = sf::Text(_label, font, _textSize);
        _shadow.setFont(font);
        updateButton();
    }


    void AnimatedButton::setLabel(std::string label) {
        _text.setString(label);
        updateButton();
    }

    void AnimatedButton::setFont(sf::Font &font) {
        _text.setFont(font);
        updateButton();
    }

    void AnimatedButton::setFontSize(unsigned int size) {
        _textSize = size;
        _text.setCharacterSize(_textSize);
        updateButton();
    }

    void AnimatedButton::setColors(sf::Color background, sf::Color border, sf::Color text) {
        _normal = {background, border, text};
        _hover = {fgcu::AzulUtility::lighten(background, .25), fgcu::AzulUtility::lighten(background, .25), text};
        _clicked = {fgcu::AzulUtility::lighten(background, .5), fgcu::AzulUtility::lighten(background, .5), text};
        _disabled = {fgcu::AzulUtility::lighten(background, .95), fgcu::AzulUtility::lighten(background, .95), fgcu::AzulUtility::lighten(text, .5)};
        updateColors();
    }

    void AnimatedButton::setPosition(sf::Vector2f position) {
        updateButton();
        _button.setPosition(position);
        sf::Vector2f textPosition = sf::Vector2f(_button.getPosition().x, _button.getPosition().y - _button.getGlobalBounds().height/4);
        _text.setPosition(textPosition);
        _shadow.setPosition(_text.getPosition().x + 3.f, _text.getPosition().y + 3.f);
    }

    bool AnimatedButton::contains(sf::Vector2f point) {
        sf::FloatRect bounds = _button.getLocalBounds();
        sf::Vector2f position = _button.getPosition();
        sf::Vector2f origin = _button.getOrigin();
        bounds.left = position.x - origin.x;
        bounds.top = position.y - origin.y;

        return bounds.contains(point);
    } // contains

    bool AnimatedButton::isDisabled() { return _state == Disabled; }
    void AnimatedButton::setDisabled(bool disable) {
        if (disable)
            _state = Disabled;
        else
            _state = Normal;
        updateColors();
    }

    bool AnimatedButton::isHovered() { return _state == Hovered; }
    void AnimatedButton::setHovered(bool hovered) {
        if (hovered) {
            _state = Hovered;
        }
        else {
            _state = Normal;
        }
        updateColors();
    }

    bool AnimatedButton::isClicked() { return _state == Clicked; }
    void AnimatedButton::setClicked(bool clicked) {
        if (clicked) {
            _state = Clicked;
        }
        else {
            _state = Normal;
        }
        updateColors();
    }

    bool AnimatedButton::checkHovered(sf::Event event, sf::RenderWindow& window) {
        bool hovered = false;

        if (event.type == sf::Event::MouseMoved) {
            auto mouse = sf::Vector2f(float(sf::Mouse::getPosition(window).x),
                                      float(sf::Mouse::getPosition(window).y));
            if (contains(mouse)) {
                if (_state == Normal) {
                    _state = Hovered;
                    updateColors();
                    hovered = true;
                }
            }
            else {
                if (_state == Hovered) {
                    _state = Normal;
                    updateColors();
                }
            }

        } // MouseMoved

        return hovered;
    } // checkHovered

    bool AnimatedButton::checkClicked(sf::Event event) {
        bool clicked = false;

        if (_state != Disabled) {
            if (_state != Clicked && event.type == sf::Event::MouseButtonPressed) {
                auto mouse = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                if (contains(mouse)) {
                    _state = Clicked;
                    updateColors();
                    clicked = true;
                }
            }
            else if (_state == Clicked && event.type == sf::Event::MouseButtonReleased) {
                auto mouse = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                if (contains(mouse)) {
                    _state = Hovered;
                    updateColors();
                    clicked = false;
                }
            }
        }

        return clicked;
    } // checkClicked

    void AnimatedButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(_button);
        target.draw(_text);
    }

    void AnimatedButton::updateButton() {
        _button.setSize(sf::Vector2f{_text.getGlobalBounds().width * 1.5f, _text.getGlobalBounds().height * 1.5f});
        _button.setOrigin(_button.getGlobalBounds().width / 2.f, _button.getGlobalBounds().height / 2.f);
        _button.setOutlineThickness(2.f);
        _button.setCornersRadius(5.f);
        _button.setCornerPointCount(20);

        _text.setOrigin(_text.getGlobalBounds().width / 2.f, _text.getGlobalBounds().height / 2.f);
        _shadow = _text;
        _shadow.setOrigin(_shadow.getGlobalBounds().width/2.f, _shadow.getGlobalBounds().height/2.f);
        _shadow.setFillColor(sf::Color::Black);
    } // updateButton

    void AnimatedButton::updateColors() {
        switch(_state) {
            case Normal:
                _button.setFillColor(_normal.background);
                _button.setOutlineColor(_normal.border);
                _text.setFillColor(_normal.text);
                break;
            case Hovered:
                _button.setFillColor(_hover.background);
                _button.setOutlineColor(_hover.border);
                _text.setFillColor(_hover.text);
                break;
            case Clicked:
                _button.setFillColor(_clicked.background);
                _button.setOutlineColor(_clicked.border);
                _text.setFillColor(_clicked.text);
                break;
            case Disabled:
                _button.setFillColor(_disabled.background);
                _button.setOutlineColor(_disabled.border);
                _text.setFillColor(_disabled.text);
        }
    } // updateColors


} // fgcu