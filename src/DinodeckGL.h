#if ANDROID

#include <GLES/gl.h>
#include <GLES/glext.h>

#elif __APPLE__

#include <OpenGL/gl.h>
#define glOrthof glOrtho

#else

#include <gl/gl.h>
#define glOrthof glOrtho

#endif