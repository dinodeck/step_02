#include "DDFile.h"

#include <stdio.h>
#include <string.h> // for memcpy

#include "physfs.h"

DDFile* DDFile::OpenFile = NULL;

DDFile::DDFile(const char* filename)
    : mName(filename), mBuffer(NULL), mSize(0)
{

}

DDFile::~DDFile()
{
    ClearBuffer();
}

bool DDFile::LoadFileIntoBuffer()
{

    OpenFile = this;
    bool result = false;
    const char* path = mName.c_str();
    PHYSFS_file* physFile = PHYSFS_openRead(path);


    if(!physFile)
    {
        OpenFile = NULL;
        printf("Failed to open [%s]\n", path);
        return false;
    }

    ClearBuffer();

    mSize = PHYSFS_fileLength(physFile);
    mBuffer = new char[mSize * sizeof(char)];
    PHYSFS_read(physFile, (void*)mBuffer, 1, mSize);
    PHYSFS_close(physFile);

    OpenFile = NULL;
    return result;
}

void DDFile::ClearBuffer()
{
    if(mBuffer)
    {
        delete[] mBuffer;
        mBuffer = NULL;
        mSize = 0;
    }
}

void DDFile::SetBuffer(char* pData, int iSize)
{
    ClearBuffer();
    mBuffer = new char[iSize];
    memcpy( mBuffer, pData, sizeof(char)*iSize );
    mSize = iSize;
}