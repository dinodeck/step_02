#ifndef RESOURCESTORE_H
#define RESOURCESTORE_H
#include <string>
#include <map>
#include "Resource.h"

class IResourceLoader;

class ResourceStore
{
private:
	std::map<std::string, Resource> mStore;
public:
	ResourceStore();
	~ResourceStore();
	void Add(const char* name, const char* path, IResourceLoader* callback);
	void Reload();
};

#endif