#pragma once

#include <QOpenGLFunctions_4_5_Core>

class OpenGLFunctions : public QOpenGLFunctions_4_5_Core {
public:
    static OpenGLFunctions* getInstance(void);

    OpenGLFunctions(const OpenGLFunctions& other) = delete;
    void operator=(const OpenGLFunctions& other) = delete;

private:
    OpenGLFunctions(void) = default;
    ~OpenGLFunctions(void) = default;

    static OpenGLFunctions* s_instance; 
};