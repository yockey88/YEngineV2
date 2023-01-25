#ifndef GL_ERROR_HELPER_HPP
#define GL_ERROR_HELPER_HPP

#include "log.hpp"
#include "glad/glad.h"
#include <string>

namespace Y {
namespace graphics {

    void CheckGLError();
    
}
}

#ifndef Y_CONFIG_RELEASE
#define Y_CHECK_GL_ERROR Y::graphics::CheckGLError(); 
#else
#define Y_CHECK_GL_ERROR (void*)0
#endif

#endif