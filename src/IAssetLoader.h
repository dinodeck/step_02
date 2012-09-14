#ifndef IASSETLOADER_H
#define IASSETLOADER_H

#include <stdio.h>
class Asset;

class IAssetLoader
{
public:
	virtual bool Reload(Asset& asset) = 0;
	virtual ~IAssetLoader() {};
};

#endif