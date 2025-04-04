#pragma once

#include <Windows.h>
#include <gl/gl.h>

#include "third-party/opengl/glext.h"
#include "third-party/opengl/wglext.h"

#define FOR_OPENGL_FUNCTIONS(DO)                                      \
    DO(::PFNGLATTACHSHADERPROC, glAttachShader)                       \
    DO(::PFNGLBINDBUFFERPROC, glBindBuffer)                           \
    DO(::PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)                 \
    DO(::PFNGLBUFFERDATAPROC, glBufferData)                           \
    DO(::PFNGLCOMPILESHADERPROC, glCompileShader)                     \
    DO(::PFNGLCREATEPROGRAMPROC, glCreateProgram)                     \
    DO(::PFNGLCREATESHADERPROC, glCreateShader)                       \
    DO(::PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback)       \
    DO(::PFNGLDELETEBUFFERSPROC, glDeleteBuffers)                     \
    DO(::PFNGLDELETEPROGRAMPROC, glDeleteProgram)                     \
    DO(::PFNGLDELETESHADERPROC, glDeleteShader)                       \
    DO(::PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays)           \
    DO(::PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
    DO(::PFNGLGENBUFFERSPROC, glGenBuffers)                           \
    DO(::PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)                 \
    DO(::PFNGLGETSHADERIVPROC, glGetShaderiv)                         \
    DO(::PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)           \
    DO(::PFNGLLINKPROGRAMPROC, glLinkProgram)                         \
    DO(::PFNGLSHADERSOURCEPROC, glShaderSource)                       \
    DO(::PFNGLUSEPROGRAMPROC, glUseProgram)                           \
    DO(::PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)

#define DO_DEFINE(TYPE, NAME) inline TYPE NAME;
FOR_OPENGL_FUNCTIONS(DO_DEFINE)
