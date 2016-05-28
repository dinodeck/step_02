#ifndef MAIN_H
#define MAIN_H

struct SDL_Surface;
union SDL_Event;
class Dinodeck;

class Main
{
private:
	SDL_Surface*   mSurface;
	bool           mRunning;
	Dinodeck*      mDinodeck;

    void OnEvent(SDL_Event* event);
	bool ResetRenderWindow();
public:
	void Execute();
	bool Reset();
	Main();
	~Main();
};

#endif