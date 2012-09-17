#if ANDROID
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#include <gl/gl.h>
#define glOrthof glOrtho
#endif