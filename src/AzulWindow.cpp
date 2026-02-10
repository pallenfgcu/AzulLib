//
// Created by pallen on 11/25/2023.
//
#include "azul/AzulWindow.h"
#include "azul/AzulUtility.h"
#include "azul/AzulSprites.h"
#include "azul/RobotoMonoFont.h"
#include <algorithm> // swap
#include <cmath> // round, fmod

#include <iostream>

namespace fgcu {

    AzulWindow::AzulWindow(int rows, int columns, const std::string& title) :
            _dimensions{rows, columns}, _title{title}, _cellSize{0.f},
            _window(sf::VideoMode(WindowWidth, WindowHeight), title) {

        _window.setFramerateLimit(FPS);

        _backgroundColor = AzulUtility::lighten(fgcu::BackgroundColor, 0.75);
    } // constructor

    void AzulWindow::init(int rows, int columns, const std::string& title) {
        _dimensions = sf::Vector2i{columns, rows};
        _title = title;

        // load resources

        // load font sheet
        _font.loadFromMemory(fgcu::RobotoMono_Regular_ttf, fgcu::RobotoMono_Regular_ttf_len);

        // load sprite sheet
        _azulImages.loadFromMemory(fgcu::azul_sprites_png, fgcu::azul_sprites_png_len);

        float azulSize = fgcu::AzulSpriteSize;

        sf::Vector2f boardSize{_dimensions.x * azulSize, _dimensions.y * azulSize};
        sf::Vector2f windowSize{boardSize.x + 2 * azulSize, boardSize.y + 2 * azulSize};

        auto desktop = sf::VideoMode::getDesktopMode();
#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC == 1
        desktop.width /= 2.f;
        desktop.height /= 2.f;
#endif
#endif
        desktop.width -= 2 * azulSize;
        desktop.height -= 2 * azulSize;

        if (windowSize.x > desktop.width || windowSize.y > desktop.height) {
            auto delta = sf::Vector2f{windowSize.x - desktop.width, windowSize.y - desktop.height};
            float factor = delta.x / windowSize.x;
            if (delta.y > delta.x)
                factor = delta.y / windowSize.y;
            azulSize -= azulSize * factor;
            boardSize = sf::Vector2f(_dimensions.x * azulSize, _dimensions.y * azulSize);
            windowSize = sf::Vector2f(boardSize.x + 2 * azulSize, boardSize.y + 2 * azulSize);
        }

        auto boardPosition = sf::Vector2f{azulSize, azulSize};

        _cellSize = azulSize;

        _window.create(sf::VideoMode(windowSize.x, windowSize.y), title);

        _cells.clear();
        _cells.resize(_dimensions.y, std::vector<AzulCell>(_dimensions.x));

        sf::Vector2f cellPosition = boardPosition;

        for (int row=0; row < rows; ++row) {
            for (int column=0; column < columns; ++column) {
                _cells[row][column] = AzulCell(_cellSize, cellPosition, row, column);
                _cells[row][column].setBackground(AzulUtility::lighten(sf::Color(FGCU_BLUE), 0.15f));
                _cells[row][column].setCapTexture(_azulImages);
                _cells[row][column].setCapFont(_font);
                cellPosition.x += _cellSize;
            }
            cellPosition.x = boardPosition.x;
            cellPosition.y += _cellSize;
        }


        // set first Azul image
        _azulRect = sf::IntRect(0, 0, fgcu::AzulSpriteSize, fgcu::AzulSpriteSize);
        _azulShape = sf::Sprite(_azulImages, _azulRect);
        _azulShape.setOrigin(fgcu::AzulSpriteSize / 2.f, fgcu::AzulSpriteSize / 2.f);
        float scale = _cellSize / (fgcu::AzulSpriteSize * AzulScale);
        _azulShape.setScale(scale, scale);
        _azulImageIndex = 0;

        _marquee = sf::Text{"Azul's World", _font};
        _marquee.setCharacterSize(24);
        auto marqueeCenter = _marquee.getGlobalBounds().getSize() / 2.f;
        auto marqueeBounds = marqueeCenter + _marquee.getLocalBounds().getPosition();
        auto marqueeRounded = sf::Vector2f{std::round(marqueeBounds.x), std::round(marqueeBounds.y)};
        _marquee.setOrigin(marqueeRounded);
        _marquee.setPosition(windowSize.x / 2.f, azulSize / 2.f);
        _marquee.setFillColor(sf::Color(FGCU_BLUE));

        _azulStart = fgcu::AnimatedButton("Start", _font, ButtonTextSize);
        _azulStart.setColors(AzulUtility::lighten(sf::Color(FGCU_GREEN), 0.25f), sf::Color(FGCU_BLUE), sf::Color(FGCU_BLUE));
        _azulStart.setPosition({boardPosition.x * 0.5f, boardPosition.y + boardSize.y * 0.25f});

        _azulSpeed = fgcu::Slider({SliderWidth, boardSize.y * 0.5f - SliderVerticalMargin},
                                  {SliderRangeMin, SliderRangeMax});
        _azulSpeed.setPosition({boardPosition.x * 0.5f, boardPosition.y + boardSize.y * 0.5f});
        _azulSpeed.setColor(sf::Color(fgcu::FGCU_GREEN));
        _azulSpeed.setBackgroundColor(_backgroundColor);
        _azulSpeed.setValue(8.f);

    } // init

    bool AzulWindow::processEvents(AzulUtility::KeyPressedState input[]) {
        bool open = true;

        sf::Event event;
        while (_window.pollEvent(event))
        {
            // check for close request
            if (event.type == sf::Event::Closed) {
                _azulState = AzulState::Closing;
                open = false; //  return closing true
            }

            // check for keyboard events
            // only watching for key being released
            else if (event.type == sf::Event::KeyReleased) {
                // if key's prior state is off
                if (!input[event.key.code].prior) {
                    // set current and prior state on
                    // will be turned off in update
                    input[event.key.code].current = true;   // detected this loop
                    input[event.key.code].prior = true;     // ignore next loop
                }
            }

            // check for mouse button press events
            else if (event.type == sf::Event::MouseButtonPressed) {
                // check start button
                if (_azulStart.checkClicked(event))
                    _azulState = AzulState::Started;
                // check azul speed slider
                _azulSpeed.checkPressed(event);
            } // MouseButtonPressed

            // check mouse button release events
            else if (event.type == sf::Event::MouseButtonReleased) {
                // check start button
                _azulStart.checkClicked(event);
                // check azul speed slider
                _azulSpeed.checkReleased(event);
            } // MouseButtonReleased

            // mouse move events
            else if (event.type == sf::Event::MouseMoved) {
                _azulStart.checkHovered(event, _window);
                // check azul speed slider
                _azulSpeed.checkDragged(event, _window);
            } // MouseMoved

        } // while events
        return open;
    }

    bool AzulWindow::update(float lag) {
        bool done = true;

        switch (_azulState) {
            case AzulState::Starting:
            case AzulState::Started:
            case AzulState::Stopped:
            case AzulState::Closing:
                break;
            case AzulState::Moving:
                if (!moveAzul(lag)) {
                    _azulMove.speed = {0.f, 0.f};
                    _azulState = AzulState::Stopped;
                }
                else {
                    done = false;
                }
                break;
            case AzulState::Colliding:
                if (!azulCollision(lag)) {
                    _azulMove.speed = {0.f, 0.f};
                    _azulState = AzulState::Stopped;
                }
                else {
                    done = false;
                }
                break;
            case AzulState::Rotating:
                if (!rotateAzul(lag)) {
                    _azulState = AzulState::Stopped;
                }
                else {
                    done = false;
                }
                break;
        }

        return done;
    } // update

    void AzulWindow::render(float lag) {
        _window.clear(_backgroundColor);

        for (int row=0; row < _dimensions.y; ++row) {
            for (int column=0; column < _dimensions.x; ++column) {
                _window.draw(_cells[row][column]);
            }
        }

        sf::Sprite tempAzul = _azulShape;
        sf::Vector2f currentPosition = tempAzul.getPosition();
        float speedAdjust = _azulSpeed.getValue() * 0.25f;
        currentPosition.x += _azulMove.speed.x * speedAdjust * lag;
        currentPosition.y += _azulMove.speed.y * speedAdjust * lag;
        tempAzul.setPosition(currentPosition);
        _window.draw(tempAzul);

        _window.draw(_azulStart);
        _azulSpeed.draw(_window);

        _window.draw(_marquee);

        _window.display();
    } // render

    bool AzulWindow::moveAzul(float lag) {
        bool moving = true;

        float speedAdjust = _azulSpeed.getValue() * 0.25f;
        sf::Vector2f currentPosition = _azulShape.getPosition();
        currentPosition.x += _azulMove.speed.x * speedAdjust * lag;
        currentPosition.y += _azulMove.speed.y * speedAdjust * lag;

        bool atTarget = false;

        if (std::abs(_azulMove.speed.x) > 0.0000001f) { // moving horizontally
            if (_azulMove.speed.x > 0) { // moving east
                atTarget = currentPosition.x >= _azulMove.target.x;
            }
            else { // moving west
                atTarget = currentPosition.x <= _azulMove.target.x;
            }
        }
        else { // moving vertically
            if (_azulMove.speed.y > 0) { // moving south
                atTarget = currentPosition.y >= _azulMove.target.y;
            }
            else { // moving north
                atTarget = currentPosition.y <= _azulMove.target.y;
            }
        }

        if ( atTarget ) {
            _azulShape.setPosition(_azulMove.target);
            moving = false;
        }
        else {
            _azulShape.setPosition(currentPosition);
        }

        /*
        _azulMove.animation.frame++;

        if (_azulMove.animation.frame >= AzulAnimationFrames) {
           // _azulImageIndex = !_azulImageIndex;
            _azulMove.animation.frame = 0;
        }

        _azulRect = sf::IntRect(_azulImageIndex * fgcu::AzulSpriteSize, 0,
                                fgcu::AzulSpriteSize, fgcu::AzulSpriteSize);
        _azulShape.setTextureRect(_azulRect);
        */

        return moving;
    } // moveAzul

    bool AzulWindow::azulCollision(float lag) {
        bool colliding = true;

        if (_azulMove.animation.frame == 0) {
            if (!moveAzul(lag)) {
                std::swap(_azulMove.source, _azulMove.target);
                if (std::abs(_azulMove.speed.x) > 0.0f)
                    _azulMove.speed.x *= -1;
                else
                    _azulMove.speed.y *= -1;
                _azulMove.animation.frame++;
                _azulRect = sf::IntRect(0, fgcu::AzulSpriteSize,
                                        fgcu::AzulSpriteSize, fgcu::AzulSpriteSize);
                _azulShape.setTextureRect(_azulRect);
            }
        }
        else { // 2nd half of animation
            if (!moveAzul(lag)) {
                colliding = false;
                _azulRect = sf::IntRect(0, 0, fgcu::AzulSpriteSize, fgcu::AzulSpriteSize);
                _azulShape.setTextureRect(_azulRect);
            }
        }

        return colliding;
    } // azulCollision

    bool AzulWindow::rotateAzul(float lag) {
        bool rotating = true;

        float speedAdjust = _azulSpeed.getValue() * 0.25f;

        float currentRotation = _azulShape.getRotation();
        float rotateAdjust = _azulRotate.speed * speedAdjust * lag;
        _azulRotate.rotated += std::abs(rotateAdjust);
        float nextRotation = currentRotation + rotateAdjust;

        if (_azulRotate.rotated >= 90 ) {
            _azulShape.setRotation(_azulRotate.target);
            rotating = false;
        }
        else {
            _azulShape.setRotation(nextRotation);
        }

        return rotating;
    } // rotateAzul

    bool AzulWindow::isClosing() { return _azulState == AzulState::Closing; }

} // fgcu