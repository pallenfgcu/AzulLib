//
// Created by pallen on 11/25/2023.
//
#include "../include/azul/AzulUtility.h"
#include <cmath>

namespace fgcu {

    AzulUtility::Cardinality AzulUtility::stringToCardinality(const std::string& stringCardinal) {
        AzulUtility::Cardinality cardinal;

        if (stringCompare(stringCardinal, "North")) {
            cardinal = AzulUtility::Cardinality::North;
        }
        else if (stringCompare(stringCardinal, "South")) {
            cardinal = AzulUtility::Cardinality::South;
        }
        else if (stringCompare(stringCardinal, "East")) {
            cardinal = AzulUtility::Cardinality::East;
        }
        else if (stringCompare(stringCardinal, "West")) {
            cardinal = AzulUtility::Cardinality::West;
        }
        else {
            cardinal = AzulUtility::Cardinality::None;
        }
        return cardinal;
    } // stringToWall

    std::string AzulUtility::cardinalityToString(const Cardinality cardinal) {
        std::string stringCardinal;

        switch (cardinal) {
            case North:
                stringCardinal = "North";
                break;
            case South:
                stringCardinal = "South";
                break;
            case East:
                stringCardinal = "East";
                break;
            case West:
                stringCardinal = "West";
                break;
            default:
                stringCardinal = "None";
        }

        return stringCardinal;
    } // cardinalityToString

    bool AzulUtility::stringCompare(std::string lhs, std::string rhs) {
        bool compare = true;
        if (lhs.empty() || rhs.empty())
            return false;

        if (lhs.length() != rhs.length())
            return false;

        for (int i=0; i < lhs.length(); ++i) {
            if ((lhs[i] | 32) != (rhs[i] | 32))
                return false;
        }
        return compare;
    } // stringCompare

    void AzulUtility::initRandom() {
        std::srand(std::time(NULL));
    }

    int AzulUtility::getRandomNumber(int max, int min) {
        return rand() % max + min;
    } // getRandomNumber

    /**
    * process key input for update frames
    * @param input - current key states
    * @param key - check state of particular key
    * @return true if key is in a pressed state
    */
    bool AzulUtility::isKeyPressed(KeyPressedState input[], sf::Keyboard::Key key) {
        bool pressed = false;
        // check if key was pressed to rotate the shape
        if (input[key].prior) {
            // this is a current key press for this frame
            if (input[key].current) {
                pressed = true;
                // turn off the current flag to indicate we processed it
                input[key].current = false;
            }
            else { // we were skipping a frame
                // turn off the prior flag, so it can be picked up again
                input[key].prior = false;
            }
        }
        return pressed;
    } // is key pressed


    sf::Color AzulUtility::lighten(sf::Color color, float percent) {

        sf::Uint8 rgba[4] = {color.r, color.g, color.b, color.a};
        int min = 255;
        int minx = 0;

        for (int i=0; i<3; ++i) {
            if (rgba[i] < min) {
                min = rgba[i];
                minx = i;
            }
        }

        if (min == 255)
            return color;

        float minDiff = 255 - rgba[minx];
        float minPercent = minDiff * percent;
        float newMin = std::round(rgba[minx] + std::min(minDiff, minPercent));
        int minIncrease = newMin - rgba[minx];
        float increasePercent = minIncrease / float(minDiff);

        for (int i=0; i<3; ++i) {
            rgba[i] = std::round(rgba[i] + (255 - rgba[i]) * increasePercent);
        }

        return {rgba[0],rgba[1],rgba[2],rgba[3]};
    }

} // fgcu