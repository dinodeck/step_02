#include "Main.h"
#include <stdio.h>
#include "LuaState.h"
#include "Resource.h"
#include "ResourceStore.h"
#include <gl/gl.h>
#include "SDL/SDL.h"

bool Main::Reload(Resource& resource)
{
	printf("Reloading Manifest");
	LuaState luaState("Settings");
	bool success = luaState.DoFile(resource.Path().c_str());
	if(success)
	{
		mName = luaState.GetString("name", mName.c_str());
		mViewWidth = luaState.GetInt("width", mViewWidth);
		mViewHeight = luaState.GetInt("height", mViewHeight);
		//mName = luaState.GetEntryString("name", mName);
	}

	// If this fails, it should go back to the defaults
	ResetRenderWindow();
	return success;
}

Main::Main() :
 mName("Dancing Squid"), mSurface(0), mResourceStore(), mDeltaTime(0), mRunning(true), mViewWidth(640), mViewHeight(360)
{
	mResourceStore.Add("manifest", "manifest.lua", this);
}

void Main::OnEvent(SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_QUIT:
        {
            mRunning = false;
        } break;

        case SDL_KEYDOWN:
        {
            if(event->key.keysym.sym == SDLK_ESCAPE)
            {
                printf("Stopped looping because escape pressed.\n");
                mRunning = false;
            }
            else if(event->key.keysym.sym == SDLK_F2)
            {
				mResourceStore.Reload();
            }

        } break;
    }
}

bool Main::ResetRenderWindow()
{
    SDL_WM_SetCaption(mName.c_str(), mName.c_str());

    // SDL handles this surface memory, so it can be called multiple times without issue.
    if((mSurface = SDL_SetVideoMode(mViewWidth, mViewHeight, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
    {
        printf("Error initializing graphics: %s\n", SDL_GetError());
        return false;
    }

    SDL_WarpMouse(mViewWidth/2, mViewHeight/2);


    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, mViewWidth, mViewHeight);
     // Setups an orthographic view, should be handled by renderer.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, mViewWidth, mViewHeight, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0f);

    // Enabled blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    return true;
}


void Main::Execute()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
    	printf("SDL Failed to init");
        return;
    }

    // Allow the game pads to be polled.
    SDL_JoystickEventState(SDL_IGNORE);
    SDL_EnableUNICODE(1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  	8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 	8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    mResourceStore.Reload();

    unsigned int thisTime = 0;
    unsigned int lastTime = 0;
    unsigned int framesPerSecond = 60;
    unsigned int millisecondsPerFrame = 1000 / framesPerSecond;
    unsigned int fpsTicks = 0;

    SDL_Event event;

    while(mRunning)
    {
        // Calculate delta time
        thisTime = SDL_GetTicks(); // returns in milliseconds
        mDeltaTime = static_cast<double>((thisTime - lastTime) / 1000); // convert to seconds
        lastTime = thisTime;

        while(SDL_PollEvent(&event))
        {
            OnEvent(&event);
        }

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        OnUpdate();

		fpsTicks = SDL_GetTicks() - fpsTicks;
        if (fpsTicks < millisecondsPerFrame)
        {
            SDL_Delay(millisecondsPerFrame - fpsTicks);
        }
    	SDL_GL_SwapBuffers();
    }

    SDL_Quit();

	return;
}

void Main::OnUpdate()
{
	// Game code goes here.
}

int main(int argc, char *argv[]){
	Main main;
	main.Execute();
	return 0;
}