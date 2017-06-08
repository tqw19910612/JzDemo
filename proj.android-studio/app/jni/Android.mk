LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_CPPFLAGS := -std=c++11 -pthread -frtti -fexceptions

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../../Classes/AppDelegate.cpp \
#                   ../../../Classes/HelloWorldScene.cpp

#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
#-------------------------------------------------------------------#
SRC_SUFFIX := *.cpp *.c *pb.cc *cc
SRC_ROOT := $(LOCAL_PATH)/../../../Classes

# ASIO library is set as ASIO_HEADER_ONLY, so it will be excluded
EXCLUDE_LIB := testing
# exclude dirs
EXLUDE_DIR := ios

# recursive wildcard
rwildcard = $(foreach d,$(wildcard $1*),$(if $(findstring $(EXCLUDE_LIB),$d),,$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d)))
SRC_FILES := $(call rwildcard,$(SRC_ROOT)/,$(SRC_SUFFIX))
SRC_FILES := $(filter-out $(EXLUDE_DIR),$(SRC_FILES))

LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(SRC_FILES:$(LOCAL_PATH)/%=%)

SRC_DIRS := $(shell find $(SRC_ROOT) -type d)
SRC_DIRS := $(filter-out $(EXLUDE_DIR),$(SRC_DIRS))
LOCAL_C_INCLUDES := $(SRC_DIRS)
#-------------------------------------------------------------------#

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
