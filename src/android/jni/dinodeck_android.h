
//ANDROID
#include <jni.h>



#ifdef __cplusplus
extern "C" {
#endif

/* External Java functions are defined here.
   i.e. JNIEXPORT void JNICALL Java_com_dinodeck_test_appRenderer_nativeRender
        (JNIEnv *, jobject obj);
*/

    //
    // ACTIVITY (MAIN JAVA CLASS)
    //
    JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDActivity_nativeOnCreate(
        JNIEnv*, jobject obj);

    JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDActivity_nativeIFStream(
        JNIEnv*, jobject obj, jbyteArray, int);

    //
    // RENDERER
    //
    JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDRenderer_nativeClear(
        JNIEnv*, jobject obj);

    JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDRenderer_nativeUpdate(
        JNIEnv*, jobject obj, float dt);

    JNIEXPORT void JNICALL Java_com_dinodeck_dinodeck_DDRenderer_nativeResize(
        JNIEnv*, jobject obj, int width, int height, float dpiX, float dpiY);

#ifdef __cplusplus
}
#endif
