#pragma once

#include <Windows.h>
#include <gl/gl.h>

#include "third-party/opengl/glext.h"
#include "third-party/opengl/wglext.h"

#define FOR_OPENGL_FUNCTIONS(DO) \
    DO(::PFNGLCREATESHADERPROC, glCreateShader)

#if !defined(NO_EXTERN)
#define DO_EXTERN(TYPE, NAME) extern TYPE NAME;
FOR_OPENGL_FUNCTIONS(DO_EXTERN)
#else
#define DO_DEFINE(TYPE, NAME) TYPE NAME;
FOR_OPENGL_FUNCTIONS(DO_DEFINE)
#endif
