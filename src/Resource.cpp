#include "Resource.h"
#include <assert.h>
#include <stdio.h>

void Resource::Reload()
{
	assert(mLoader);
	mIsLoaded = mLoader->Reload(*this);
}

Resource::Resource(const char* name, const char* path, IResourceLoader* loader)
{
	assert(loader);
	mName = name;
	mPath = path;
	mLoader = loader;
	mIsLoaded = false;
}

void Resource::SetTimeLastModified(time_t lastModified)
{
	mLastModified = lastModified;
}