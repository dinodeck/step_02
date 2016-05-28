#include "Dinodeck.h"
#include <cstdio>

#include "Asset.h"
#include "AssetStore.h"
#include "DinodeckGL.h"
#include "LuaState.h"

DancingSquid::DancingSquid(const std::string& name)
    : mName(name), mAssetStore(), mViewWidth(640), mViewHeight(360)
{
    mAssetStore.Add("settings", "settings.lua", this);
}

DancingSquid::~DancingSquid()
{

}

bool DancingSquid::Reload(Asset& asset)
{
    LuaState luaState("Settings");
    bool success = luaState.DoFile(asset.Path().c_str());
    if(success)
    {
        std::string name = luaState.GetString("name", Name().c_str());
        int width = luaState.GetInt("width", ViewWidth());
        int height = luaState.GetInt("height", ViewHeight());
        SetName(name);
        ResetRenderWindow(width, height);
    }

    return success;
}

void DancingSquid::ForceReload()
{
    mAssetStore.Reload();
    printf("After ForceReload.\n");
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
    glClearColor(0.0, 1.0, 1.0, 1.0f);

    // Enabled blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}