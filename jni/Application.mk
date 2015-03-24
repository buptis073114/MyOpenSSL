NDK_TOOLCHAIN_VERSION=4.9
APP_PROJECT_PATH := $(shell pwd)
APP_BUILD_SCRIPT := $(APP_PROJECT_PATH)/Android.mk
APP_ABI  := armeabi armeabi-v7a x86 mips
APP_PLATFORM  := android-10