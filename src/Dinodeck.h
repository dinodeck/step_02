#ifndef DINODECK_H
#define DINODECK_H
#include <string>

#include "AssetStore.h"
#include "IAssetLoader.h"

// Dancing Squid is the kernal of the engine and should have limited dependancies.
// It assumes access to OpenGL

class Asset;


class DancingSquid : IAssetLoader
{
private:
    std::string mName; // name of the game / project
    AssetStore  mAssetStore;
    // Drawable area in pixels
    unsigned int mViewWidth;
    unsigned int mViewHeight;

public:
    DancingSquid(const std::string& name);
    ~DancingSquid();
    void Update(double deltaTime);
    const std::string& Name() const { return mName; }
    void SetName(const std::string& value) { mName = value; }
    unsigned int ViewWidth() const { return mViewWidth; }
    unsigned int ViewHeight() const { return mViewHeight; }
    void ResetRenderWindow(unsigned int width, unsigned int height);
    // Callback to reload the manifest
    virtual bool Reload(Asset& asset);
    void ForceReload();
};

#endif
