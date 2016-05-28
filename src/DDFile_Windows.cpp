#include "DDFile.h"

#include <stdio.h>
#include <string.h> // for memcpy

#include "physfs.h"

DSFile* DSFile::OpenFile = NULL;

DSFile::DSFile(const char* filename)
    : mName(filename), mBuffer(NULL), mSize(0)
{

}

DSFile::~DSFile()
{
    ClearBuffer();
}

//
// Loads a file from the APK.
// Calls OpenAsset which talks to Java
// Java calls nativeIFStream which calls
// SetBuffer
//
bool DSFile::LoadFileIntoBuffer()
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

void DSFile::ClearBuffer()
{
    if(mBuffer)
    {
        delete[] mBuffer;
        mBuffer = NULL;
        mSize = 0;
    }
}

void DSFile::SetBuffer(char* pData, int iSize)
{
    ClearBuffer();
    mBuffer = new char[iSize];
    memcpy( mBuffer, pData, sizeof(char)*iSize );
    mSize = iSize;
}