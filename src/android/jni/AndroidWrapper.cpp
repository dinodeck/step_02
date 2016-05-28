#include "AndroidWrapper.h"

#include <stdint.h>

AndroidWrapper* AndroidWrapper::Instance = NULL;

AndroidWrapper::AndroidWrapper(JNIEnv* jniEnv) :
    mJNIEnvironment(jniEnv)
{
    const char* strDDActivity = "com/dinodeck/dinodeck/DDActivity";
    mDDActivityClass = jniEnv->FindClass(strDDActivity);
    mJavaMethod_OpenAsset = jniEnv->GetStaticMethodID
    (
        mDDActivityClass,
        "open_asset",
        "(Ljava/lang/String;)Z"
    );
}

bool AndroidWrapper::OpenAsset(const char* name)
{
    jstring jStrPath = mJNIEnvironment->NewStringUTF(name);
    bool result = mJNIEnvironment->CallStaticBooleanMethod
    (
        mDDActivityClass,
        mJavaMethod_OpenAsset,
        jStrPath
    );
    mJNIEnvironment->DeleteLocalRef(jStrPath);
    return result;
}