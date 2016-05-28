#include "dinodeck_android.h"

#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <jni.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Just testing if this crashes :D
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "../../Dinodeck.h"
#include "../../DDFile.h"
#include "AndroidWrapper.h"
// Temp for testing.
#include "../../LuaState.h"
#include "../../AssetStore.h"



Dinodeck* gDinodeck = NULL;


#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "DSNDK", __VA_ARGS__)

/* External Java functions are implemented here.
*/

//
// ACTIVITY
//
JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDActivity_nativeOnCreate(
        JNIEnv* env, jobject obj)
{
    AndroidWrapper::CreateInstance(env);
    AssetStore::CleverReloadingFlag(false);
    gDinodeck = new Dinodeck("Dinodeck"); // Never deleted
}

JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDActivity_nativeIFStream(
    JNIEnv* env, jobject obj, jbyteArray arr, int iSize)
{
    jbyte* c_array = env->GetByteArrayElements(arr, NULL);

    DDFile* pOpenFile = DDFile::GetOpenFile();
    if(pOpenFile)
    {
        pOpenFile->SetBuffer((char*)(c_array), iSize);
    }

    // release the memory for java
    env->ReleaseByteArrayElements(arr, c_array, JNI_ABORT);
    env->DeleteLocalRef(arr);
}


//
// RENDERER
//

JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDRenderer_nativeClear(
    JNIEnv* pJNIEnv, jobject obj)
{
    glClearColor(0.0, 0.0, 0.0, 0.0f);
}

JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDRenderer_nativeUpdate(
    JNIEnv*, jobject obj, float dt)
{
    gDinodeck->Update(dt);
}

JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDRenderer_nativeResize(
    JNIEnv*, jobject obj, int width, int height, float dpiX, float dpiY)
{
    gDinodeck->ResetRenderWindow(width, height);
}