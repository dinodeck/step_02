#include "ResourceStore.h"
#include "IResourceLoader.h"
#include <map>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

ResourceStore::ResourceStore()
{

}

ResourceStore::~ResourceStore()
{

}

void ResourceStore::Add(const char* name, const char* path, IResourceLoader* callback)
{
	mStore.insert(std::pair<std::string, Resource>(
					std::string(name),
					Resource(name, path, callback)));
}

void ResourceStore::Reload()
{
	// Iterate through files,
	// Load if not loaded
	// Else get last modified date
	// If date is later than store date then reload
	for(std::map<std::string, Resource>::iterator it = mStore.begin(); it != mStore.end(); ++it)
	{
		// Not doing date thing yet
		Resource& resource = it->second;

		// Be careful when loading from a package.
		struct stat s;
		time_t lastModified = time(NULL);
		if(stat(resource.Path().c_str(), &s) == 0)
		{
			lastModified = s.st_mtime;
		}

		if(resource.IsLoaded() && lastModified <= resource.LastModified())
		{
			printf("%s already loaded.\n", resource.Name().c_str());
		}
		else
		{
			printf("Loaded [%s] Last Modified [%s]\n", resource.Name().c_str(), ctime(&lastModified));
			resource.Reload();
			resource.SetTimeLastModified(lastModified);
		}
	}
}
