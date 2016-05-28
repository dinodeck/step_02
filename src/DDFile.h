#ifndef DDFILE
#define DDFILE

#include <string>



class DSFile
{
private:
    // Used to communicate asset loading w/ android
    static DSFile* OpenFile;
    std::string mName;
    char* mBuffer;
    unsigned int mSize;
public:
    static DSFile* GetOpenFile() { return DSFile::OpenFile; }
    DSFile(const char* filename);
    ~DSFile();
    bool LoadFileIntoBuffer();
    void SetBuffer(char* pData, int iSize);
    const char* Buffer() { return mBuffer; }
    unsigned int Size() { return mSize; }
    void ClearBuffer();

};

#endif