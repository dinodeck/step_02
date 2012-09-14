#ifndef MAIN_H
#define MAIN_H
#include <string>
#include "IAssetLoader.h"
#include "AssetStore.h"


struct SDL_Surface;
union SDL_Event;
class DancingSquid;
class Asset;

class Main : IAssetLoader
{
private:
	SDL_Surface* 	mSurface;
	AssetStore 		mAssetStore;
	bool 			mRunning;
	DancingSquid*	mDancingSquid;

    void OnEvent(SDL_Event* event);
	bool ResetRenderWindow(unsigned int width, unsigned int height);
public:
	// Callback to reload the manifest
	virtual bool Reload(Asset& asset);
	void Execute();
	bool Reset();
	Main();
	~Main();
};

#endif