#include "DancingSquid.h"
#include <cstdio>

#if ANDROID
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#include <gl/gl.h>
#define glOrthof glOrtho
#endif


DancingSquid::DancingSquid(const std::string& name)
    : mName(name), mViewWidth(640), mViewHeight(360)
{

}

DancingSquid::~DancingSquid()
{

}

//
// @deltaTime Number of seconds last frame took
//              * Capped to 1/60 on Windows
void DancingSquid::Update(double deltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DancingSquid::ResetRenderWindow(unsigned int width, unsigned int height)
{
    mViewWidth = width;
    mViewHeight = height;
    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, mViewWidth, mViewHeight);

     // Setups an orthographic view, should be handled by renderer.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0, mViewWidth, mViewHeight, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    glClearColor(0.0, 1.0, 0.0, 1.0f);

    // Enabled blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}