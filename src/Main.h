#ifndef MAIN_H
#define MAIN_H
#include <string>
#include "IResourceLoader.h"
#include "ResourceStore.h"


struct SDL_Surface;
union SDL_Event;

class Resource;

class Main : IResourceLoader
{
private:
	std::string		mName;
	SDL_Surface* 	mSurface;
	ResourceStore 	mResourceStore;
	double 			mDeltaTime;
	bool 			mRunning;
	int 			mViewWidth;
    int 			mViewHeight;
    void OnEvent(SDL_Event* event);
	void OnUpdate();
	bool ResetRenderWindow();
public:
	// Callback to reload the manifest
	virtual bool Reload(Resource& resource);
	void Execute();
	bool Reset();
	Main();
};

#endif