#ifndef ASSETSTORE_H
#define ASSETSTORE_H
#include <string>
#include <map>
#include "Asset.h"

class IResourceLoader;

class AssetStore
{
private:
    static bool CleverReloading;
	std::map<std::string, Asset> mStore;
public:
    static void CleverReloadingFlag(bool value)
    {
        AssetStore::CleverReloading = value;
    }
	AssetStore();
	~AssetStore();
	void Add(const char* name, const char* path, IAssetLoader* callback);
	void Reload();
};

#endif