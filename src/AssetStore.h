#ifndef ASSETSTORE_H
#define ASSETSTORE_H
#include <string>
#include <map>
#include "Asset.h"

class IResourceLoader;

class AssetStore
{
private:
	std::map<std::string, Asset> mStore;
public:
	AssetStore();
	~AssetStore();
	void Add(const char* name, const char* path, IAssetLoader* callback);
	void Reload();
};

#endif