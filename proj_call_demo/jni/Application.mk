
# Build both ARMv5TE and ARMv7-A machine code.

APP_ABI := armeabi armeabi-v7a 

# Set target Android API level to the application's minimum SDK version.

APP_PLATFORM := android-9

# Include STL port lib

APP_STL := stlport_static