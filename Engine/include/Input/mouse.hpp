#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <array>

namespace Y {

namespace input {

    class mouse {
        constexpr static const int ButtonCount = 5;

        static int x , xLast;
        static int y , yLast;

        static std::array<bool , ButtonCount> buttons;
        static std::array<bool , ButtonCount> buttonsLast;
        public:
            static void initialize();
            static void  update();

            inline static int X() { return x; }
            inline static int Y() { return y; }

            inline static int DX() { return x - xLast; }
            inline static int DY() { return y - yLast; }

            static bool button(int button);
            static bool buttonDown(int button);
            static bool buttonUp(int button);

            static void printMousePos();
    };

} // End of input

} // End of Y

enum {
    Y_INPUT_MOUSE_FIRST = 1 ,
    Y_INPUT_MOUSE_LEFT = Y_INPUT_MOUSE_FIRST ,
    Y_INPUT_MOUSE_MIDDLE = 2 ,
    Y_INPUT_MOUSE_RIGHT = 3 ,
    Y_INPUT_MOUSE_X1 = 4 ,
    Y_INPUT_MOUSE_X2 = 5 ,
    Y_INPUT_MOUSE_LAST = 5
};

#endif /* mous.hpp */