#include "../../DSFile.h"

#include <fstream>
#include <jni.h>
#include <unistd.h>

#include "AndroidWrapper.h"

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
    AndroidWrapper* wrapper = AndroidWrapper::GetInstance();
    bool result = wrapper->OpenAsset(mName.c_str());
    OpenFile = NULL;
    return result;
}

void DSFile::SetBuffer(char* pData, int iSize)
{
    ClearBuffer();
    mBuffer = new char[iSize];
    memcpy( mBuffer, pData, sizeof(char)*iSize );
    mSize = iSize;
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