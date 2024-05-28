//
// Created by pallen on 11/25/2023.
//
#include <string>
#include <cstdlib>  // rand,srand
#include <ctime>    // seed srand
#include <SFML/Graphics.hpp>

#ifndef AZUL_UTILITY_H
#define AZUL_UTILITY_H

namespace fgcu {


    class AzulUtility {

    public:

        struct KeyPressedState {    // maintain state of each input key across frames
            bool prior;             // state of key in prior frame: Pressed = true
            bool current;           // state of key for this frame: Pressed = true
        };

        enum Cardinality {
            None = 0,
            North = 1,
            South = 2,
            East = 4,
            West = 8
        };

        static Cardinality stringToCardinality(const std::string& stringCardinal);

        static std::string cardinalityToString(Cardinality cardinal);

        static bool stringCompare(std::string lhs, std::string rhs);

        static void initRandom();

        static int getRandomNumber(int max=2, int min=0);

        static bool isKeyPressed(KeyPressedState input[], sf::Keyboard::Key key);

        static sf::Color lighten(sf::Color color, float percent);
    };


} // fgcu


#endif //AZUL_UTILITY_H
