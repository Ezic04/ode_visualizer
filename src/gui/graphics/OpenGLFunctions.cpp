#include "gui/graphics/OpenGLFunctions.hpp"

OpenGLFunctions* OpenGLFunctions::s_instance = nullptr;

OpenGLFunctions* OpenGLFunctions::getInstance(void){
    if (!s_instance) {
        s_instance = new OpenGLFunctions();
        s_instance->initializeOpenGLFunctions();
    }
    return s_instance;
}