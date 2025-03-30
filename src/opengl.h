#pragma once

#include <Windows.h>
#include <gl/gl.h>

#include "third-party/opengl/glext.h"
#include "third-party/opengl/wglext.h"

#define FOR_OPENGL_FUNCTIONS(DO)                                      \
    DO(::PFNGLCREATESHADERPROC, glCreateShader)                       \
    DO(::PFNGLDELETESHADERPROC, glDeleteShader)                       \
    DO(::PFNGLSHADERSOURCEPROC, glShaderSource)                       \
    DO(::PFNGLCOMPILESHADERPROC, glCompileShader)                     \
    DO(::PFNGLGETSHADERIVPROC, glGetShaderiv)                         \
    DO(::PFNGLCREATEPROGRAMPROC, glCreateProgram)                     \
    DO(::PFNGLDELETEPROGRAMPROC, glDeleteProgram)                     \
    DO(::PFNGLATTACHSHADERPROC, glAttachShader)                       \
    DO(::PFNGLLINKPROGRAMPROC, glLinkProgram)                         \
    DO(::PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)                 \
    DO(::PFNGLGENBUFFERSPROC, glGenBuffers)                           \
    DO(::PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)                 \
    DO(::PFNGLBINDBUFFERPROC, glBindBuffer)                           \
    DO(::PFNGLBUFFERDATAPROC, glBufferData)                           \
    DO(::PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)         \
    DO(::PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
    DO(::PFNGLUSEPROGRAMPROC, glUseProgram)                           \
    // DO(::PFNGLDRAWARRAYSEXTPROC, glDrawArraysEXT)

#define DO_DEFINE(TYPE, NAME) inline TYPE NAME;
FOR_OPENGL_FUNCTIONS(DO_DEFINE)
