#include "AssetStore.h"

#include <map>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <time.h>

#include "IAssetLoader.h"

bool AssetStore::CleverReloading = true;

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
		Asset& asset = it->second;

		if(false == AssetStore::CleverReloading)
		{
			asset.Reload();
			continue;
		}

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
			std::string timeString(ctime(&lastModified));
			// Remove trailing \n from time string
			{
				size_t end = timeString.find_last_of('\n');
				timeString = timeString.substr(0, end);
			}
			printf
			(
			 	"Loaded [%s] Last Modified [%s]\n",
			    asset.Name().c_str(),
			    timeString.c_str()
			);
			asset.Reload();
			asset.SetTimeLastModified(lastModified);
		}
	}
}
