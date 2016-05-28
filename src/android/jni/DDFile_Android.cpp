#include "../../DDFile.h"

#include <fstream>
#include <jni.h>
#include <unistd.h>

#include "AndroidWrapper.h"

DDFile* DDFile::OpenFile = NULL;

DDFile::DDFile(const char* filename)
    : mName(filename), mBuffer(NULL), mSize(0)
{

}

DDFile::~DDFile()
{
    ClearBuffer();
}

//
// Loads a file from the APK.
// Calls OpenAsset which talks to Java
// Java calls nativeIFStream which calls
// SetBuffer
//
bool DDFile::LoadFileIntoBuffer()
{
    OpenFile = this;
    AndroidWrapper* wrapper = AndroidWrapper::GetInstance();
    bool result = wrapper->OpenAsset(mName.c_str());
    OpenFile = NULL;
    return result;
}

void DDFile::SetBuffer(char* pData, int iSize)
{
    ClearBuffer();
    mBuffer = new char[iSize];
    memcpy( mBuffer, pData, sizeof(char)*iSize );
    mSize = iSize;
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