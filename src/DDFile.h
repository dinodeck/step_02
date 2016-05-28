#ifndef DDFILE
#define DDFILE

#include <string>



class DDFile
{
private:
    // Used to communicate asset loading w/ android
    static DDFile* OpenFile;
    std::string mName;
    char* mBuffer;
    unsigned int mSize;
public:
    static DDFile* GetOpenFile() { return DDFile::OpenFile; }
    DDFile(const char* filename);
    ~DDFile();
    bool LoadFileIntoBuffer();
    void SetBuffer(char* pData, int iSize);
    const char* Buffer() { return mBuffer; }
    unsigned int Size() { return mSize; }
    void ClearBuffer();

};

#endif