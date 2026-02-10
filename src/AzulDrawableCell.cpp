//
// Created by pallen on 11/25/2023.
//

#include "azul/AzulDrawableCell.h"
#include "azul/AzulWindow.h"
#include "azul/AzulUtility.h"

namespace fgcu {

    AzulDrawableCell::AzulDrawableCell() :
            _size{0.f}, _row{0}, _column{0}, _showCap{false} { }

    AzulDrawableCell::AzulDrawableCell(float size, sf::Vector2f position, int row, int column) :
            _size{size}, _row{row}, _column{column} {

        _block.setSize(sf::Vector2f(_size, _size));
        _block.setPosition(position);
        _block.setFillColor(fgcu::BackgroundColor);
        _block.setOutlineThickness(-1);
        _block.setOutlineColor(fgcu::BorderColor);

        _dot.setRadius(fgcu::DotRadius);
        _dot.setPosition(position.x + _size / 2.f, position.y + _size / 2.f);
        _dot.setFillColor(fgcu::BorderColor);

        _northWall.setSize(sf::Vector2f(_size, fgcu::WallWidth));
        _northWall.setPosition(position);
        _northWall.setFillColor(sf::Color::Transparent);

        _southWall.setSize(sf::Vector2f(_size, fgcu::WallWidth));
        _southWall.setPosition(position.x, position.y + _size - fgcu::WallWidth);
        _southWall.setFillColor(sf::Color::Transparent);

        _eastWall.setSize(sf::Vector2f(fgcu::WallWidth, _size));
        _eastWall.setPosition(position.x + _size - fgcu::WallWidth, position.y);
        _eastWall.setFillColor(sf::Color::Transparent);

        _westWall.setSize(sf::Vector2f(fgcu::WallWidth, _size));
        _westWall.setPosition(position);
        _westWall.setFillColor(sf::Color::Transparent);

        _showCap = false;

    } // constructor

    void AzulDrawableCell::setBackground(sf::Color background) {
        _block.setFillColor(background);
    }

    void AzulDrawableCell::setCapTexture(const sf::Texture& capImage) {
        // cap is in bottom right corner of sprite sheet
        auto capRect = sf::IntRect(fgcu::AzulSpriteSize, fgcu::AzulSpriteSize,
                                   fgcu::AzulSpriteSize, fgcu::AzulSpriteSize);
        _capSprite = sf::Sprite(capImage, capRect);
        _capSprite.setOrigin(_capSprite.getLocalBounds().width / 2.f,
                             _capSprite.getLocalBounds().height / 2.f);
        _capSprite.setPosition(_block.getPosition().x + _size / 2.f,
                               _block.getPosition().y + _size / 2.f);
    }

    void AzulDrawableCell::setCapFont(const sf::Font& capFont) {
        _capText.setFont(capFont);
    }

    void AzulDrawableCell::setCapText(const std::string& text) {
        _capText.setString(text);
        _capText.setCharacterSize(fgcu::CapTextSize);
        _capText.setFillColor(fgcu::CapTextColor);
        auto center = _capText.getGlobalBounds().getSize() / 2.f;
        auto localBounds = center + _capText.getLocalBounds().getPosition();
        _capText.setOrigin(localBounds);
        _capText.setPosition(_block.getPosition().x + _size / 2.f,
                             _block.getPosition().y + _size / 2.f);
    }

    void AzulDrawableCell::turnOnWall(AzulUtility::Cardinality side) {
        switch(side) {
            case AzulUtility::Cardinality::North:
                _northWall.setFillColor(fgcu::WallColor);
                break;
            case AzulUtility::Cardinality::South:
                _southWall.setFillColor(fgcu::WallColor);
                break;
            case AzulUtility::Cardinality::East:
                _eastWall.setFillColor(fgcu::WallColor);
                break;
            case AzulUtility::Cardinality::West:
                _westWall.setFillColor(fgcu::WallColor);
        }
    } // turnOnWall

    void AzulDrawableCell::turnOffWall(AzulUtility::Cardinality side) {
        switch(side) {
            case AzulUtility::Cardinality::North:
                _northWall.setFillColor(sf::Color::Transparent);
                break;
            case AzulUtility::Cardinality::South:
                _southWall.setFillColor(sf::Color::Transparent);
                break;
            case AzulUtility::Cardinality::East:
                _eastWall.setFillColor(sf::Color::Transparent);
                break;
            case AzulUtility::Cardinality::West:
                _westWall.setFillColor(sf::Color::Transparent);
        }
    } // turnOnWall

    void AzulDrawableCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(_block);
        target.draw(_dot);
        target.draw(_northWall);
        target.draw(_southWall);
        target.draw(_eastWall);
        target.draw(_westWall);
        if (_showCap) {
            target.draw(_capSprite);
            target.draw(_capText);
        }
    } // draw

    sf::Vector2f AzulDrawableCell::getCellPosition() const {
        return _block.getPosition();
    }

    sf::Vector2f AzulDrawableCell::getCellCenter() const {
        auto location = getCellPosition();
        location.x += _size / 2.f;
        location.y += _size / 2.f;
        return location;
    }

    sf::FloatRect AzulDrawableCell::getCellBounds() const {
        return {getCellPosition(), sf::Vector2f{_size, _size}};
    }

} // fgcu

