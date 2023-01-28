#ifndef HELPER_HPP
#define HELPER_HPP

#include "log.hpp"
#include "glad/glad.h"
#include <string>

namespace Y {
namespace graphics {

    void checkGLError();
    
}
}

#ifndef Y_CONFIG_RELEASE
#define Y_CHECK_GL_ERROR Y::graphics::checkGLError(); 
#else
#define Y_CHECK_GL_ERROR (void*)0
#endif


#endif