#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <ctime>
#include "IResourceLoader.h"

//
// A resource is something the game uses such as a script file, texture or model
//
class Resource
{
private:
	std::string mPath;
	std::string mName;
	bool mIsLoaded;
	IResourceLoader* mLoader;
	time_t mLastModified;
public:
	Resource(const char* name, const char* path, IResourceLoader* loader);
	void Reload();
	const std::string& Path() const { return mPath; }
	bool IsLoaded() const { return mIsLoaded; }
	const std::string& Name() const { return mName; }
	void SetTimeLastModified(time_t lastModified);
	time_t LastModified() const { return mLastModified; }
};


#endif
