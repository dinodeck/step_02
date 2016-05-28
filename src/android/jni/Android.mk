
#JNI make file
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := lua
LOCAL_SRC_FILES :=  luajit/libluajit.a
LOCAL_EXPORT_C_INCLUDES :=  $(LOCAL_PATH)/luajit/
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := dinodeck
LOCAL_STATIC_LIBRARIES := lua
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := ../../LuaState.cpp \
    ../../Asset.cpp \
    ../../AssetStore.cpp \
    ../../Dinodeck.cpp \
    AndroidWrapper.cpp \
    DDFile_Android.cpp \
    dinodeck_android.cpp
LOCAL_LDLIBS    := -llog -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)