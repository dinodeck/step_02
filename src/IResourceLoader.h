#ifndef IRESOURCELOADER_H
#define IRESOURCELOADER_H

#include <stdio.h>
class Resource;

class IResourceLoader
{
public:
	virtual bool Reload(Resource& resource) = 0;
	virtual ~IResourceLoader() {};
};

#endif