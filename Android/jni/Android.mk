LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_INSTALL_MODULES := on
INSTALL_CUDA_LIBRARIES := on
include $(OPENCV_ANDROID)\sdk\native\jni\OpenCV.mk
LOCAL_MODULE    := PanoramaTrackerAndroid
LOCAL_C_INCLUDES := $(OPENCV_ANDROID)\sdk\native\jni\include
LOCAL_ALLOW_UNDEFINED_SYMBOLS:=true 
FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
include $(BUILD_SHARED_LIBRARY)
