LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#APP_STL:=c++_shared 
APP_STL:=gnustl_static
APP_CPPFLAGS := -frtti -fexceptions -std=c++11
APP_ABI := armeabi-v7a
APP_OPTIM:= release
include $(BUILD_SHARED_LIBRARY)
