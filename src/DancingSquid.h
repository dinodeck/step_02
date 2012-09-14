#ifndef DANCINGSQUID_H
#define DANCINGSQUID_H
#include <string>

// Dancing Squid is the kernal of the engine and should have limited dependancies.
// It assumes access to OpenGL

class DancingSquid
{
private:
    std::string mName; // name of the game / project
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
};

#endif
