#ifndef ANDROIDWRAPPER_H
#define ANDROIDWRAPPER_H

#include <jni.h>
// There are AssetManager classes but they're
// only available in SDK > 9
// We're looking to support 2.2 as minimum
// So that option is not open



class AndroidWrapper
{
private:
    static AndroidWrapper* Instance;
    JNIEnv* mJNIEnvironment;
    jclass mDSActivityClass;
    jmethodID mJavaMethod_OpenAsset;
public:
    static void CreateInstance(JNIEnv* jniEnv)
    {
        // Never deleted.
        AndroidWrapper::Instance = new AndroidWrapper(jniEnv);
    };
    static AndroidWrapper* GetInstance() { return AndroidWrapper::Instance; }

    AndroidWrapper(JNIEnv* jniEnv);

    JNIEnv* GetJNIEnv() { return mJNIEnvironment; }
    jclass GetDSAcivityClass() { return mDSActivityClass; }

    // Functions on the Java side
    bool OpenAsset(const char* name);
};

#endif