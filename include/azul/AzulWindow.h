//
// Created by pallen on 11/25/2023.
//
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../../include/azul/AzulCell.h"
#include "../../include/azul/AzulUtility.h"
#include "../../include/azul/AnimatedButton.h"
#include "../../src/headers/Slider.h"

#ifndef AZUL_AZULWINDOW_H
#define AZUL_AZULWINDOW_H

namespace fgcu {

    const unsigned int FGCU_GREEN    = 0x007749FF;
    const unsigned int FGCU_GREEN_LT = 0xBFDDD1FF;
    const unsigned int FGCU_BLUE     = 0x002D72FF;
    const unsigned int FGCU_BLUE_LT  = 0xBFCADCFF;
    const unsigned int FGCU_GOLD     = 0xB9975BFF;
    const unsigned int FGCU_GOLD_LT  = 0xE7BC71FF;

    const int FPS = 30;     // how many update frames per second
    const int FRAME_RATE_MS = (1.f / float(FPS)); // per millisecond

    const int WindowWidth = 750;
    const int WindowHeight = 750;
    const int BoardWidth = 600;
    const int BoardHeight = 600;
    const int BoardMarginTop = 50;
    const int BoardMarginLeft = 50;
    const float BoardTop = (WindowHeight - BoardHeight) / 2.f + BoardMarginTop;
    const float BoardLeft = (WindowWidth - BoardWidth) / 2.f + BoardMarginLeft;
    const int WallWidth = 2;
    const int DotRadius = 2;
    const unsigned int AzulSpriteSize = 120;
    const float CapScale = 0.75f;
    const int CapTextSize = 16;
    const float AzulScale = 0.75f;
    const unsigned int AzulAnimationFrames = 5;
    const int ButtonTextSize = 16;
    const float SliderWidth = 10.f;
    const float SliderVerticalMargin = 20.f;
    const float SliderRangeMin = 1.f;
    const float SliderRangeMax = 40.f;

    const sf::Color BackgroundColor{FGCU_BLUE}; //sf::Color::Black;
    const sf::Color BorderColor{FGCU_GREEN}; // sf::Color(0xD3, 0xD3, 0xD3, 50); // light grey 50/255 ~20% Opacity;
    const sf::Color WallColor{FGCU_GOLD}; // sf::Color::Cyan;
    const sf::Color CapTextColor{FGCU_BLUE}; //sf::Color::Blue;

    class AzulWindow {

    protected:

        enum AzulState {
            Starting,
            Started,
            Stopped,
            Moving,
            Colliding,
            Rotating,
            Closing
        };

        struct Animation {
            int image;
            int frame;
        };

        struct MoveAzul {
            sf::Vector2f source;
            sf::Vector2f target;
            sf::Vector2f speed;
            Animation animation;
        };

        struct RotateAzul {
            int source;
            int target;
            float speed;
            float rotated;
        };

        AzulState _azulState;

        sf::RenderWindow _window;
        std::string _title;
        sf::Vector2i _dimensions;
        std::vector<std::vector<AzulCell>> _cells;
        float _cellSize;
        sf::Text _marquee;

        sf::Texture _azulImages;
        unsigned int _azulImageIndex;
        sf::Font _font;

        sf::IntRect _azulRect;
        sf::Sprite _azulShape;
        MoveAzul _azulMove;
        RotateAzul _azulRotate;

        fgcu::AnimatedButton _azulStart;
        fgcu::Slider _azulSpeed;

        sf::Color _backgroundColor;


        // Methods
        // ------------------------------------------------------------

        AzulWindow(int rows, int columns, const std::string& title);

        virtual void init(int rows, int columns, const std::string& title);

        [[nodiscard]] float getCellSize() const { return _cellSize; }

        bool processEvents(AzulUtility::KeyPressedState input[]);

        bool update(float lag);

        void render(float lag);

        bool moveAzul(float lag);

        bool azulCollision(float lag);

        bool rotateAzul(float lag);

    public:

        bool isClosing();
    };

} // fgcu

#endif //AZUL_AZULWINDOW_H
