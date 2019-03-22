#include "pointerhandler.h"

#include <iostream>

namespace bump {

void handlePointerPosition(GLFWwindow* window, double x, double y)
{
    std::cout << x << ' ' << y << std::endl;
}

} // end of namespace bump
