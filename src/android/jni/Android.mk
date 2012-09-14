
#Bigyama JNI make file
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := bigyama
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := bigyama_android.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
    