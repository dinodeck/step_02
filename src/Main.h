#ifndef MAIN_H
#define MAIN_H
#include <string>

struct SDL_Surface;
union SDL_Event;
class DancingSquid;

class Main
{
private:
	SDL_Surface* 	mSurface;
	bool 			mRunning;
	DancingSquid*	mDancingSquid;

    void OnEvent(SDL_Event* event);
	bool ResetRenderWindow();
public:
	void Execute();
	bool Reset();
	Main();
	~Main();
};

#endif