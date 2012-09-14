#include "AssetStore.h"
#include "IAssetLoader.h"
#include <map>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

AssetStore::AssetStore()
{

}

AssetStore::~AssetStore()
{

}

void AssetStore::Add(const char* name, const char* path, IAssetLoader* callback)
{
	mStore.insert(std::pair<std::string, Asset>(
					std::string(name),
					Asset(name, path, callback)));
}

void AssetStore::Reload()
{
	// Iterate through files,
	// Load if not loaded
	// Else get last modified date
	// If date is later than store date then reload
	for(std::map<std::string, Asset>::iterator it = mStore.begin(); it != mStore.end(); ++it)
	{
		// Not doing date thing yet
		Asset& asset = it->second;

		// Be careful when loading from a package.
		struct stat s;
		time_t lastModified = time(NULL);
		if(stat(asset.Path().c_str(), &s) == 0)
		{
			lastModified = s.st_mtime;
		}

		if(asset.IsLoaded() && lastModified <= asset.LastModified())
		{
			printf("%s already loaded.\n", asset.Name().c_str());
		}
		else
		{
			printf("Loaded [%s] Last Modified [%s]\n", asset.Name().c_str(), ctime(&lastModified));
			asset.Reload();
			asset.SetTimeLastModified(lastModified);
		}
	}
}
