#include "Asset.h"

#include <assert.h>
#include <stdio.h>

void Asset::Reload()
{
	assert(mLoader);
	mIsLoaded = mLoader->Reload(*this);
}

Asset::Asset(const char* name, const char* path, IAssetLoader* loader)
{
	assert(loader);
	mName = name;
	mPath = path;
	mLoader = loader;
	mIsLoaded = false;
}

void Asset::SetTimeLastModified(time_t lastModified)
{
	mLastModified = lastModified;
}