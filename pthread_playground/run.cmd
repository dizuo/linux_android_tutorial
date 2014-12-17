@echo "1. build .o file"

@Rem fPIE flag is used in compiling stage.
D:\android-ndk-r9b-windows-x86\toolchains\arm-linux-androideabi-4.6\prebuilt\windows\bin\arm-linux-androideabi-gcc.exe --sysroot=D:\android-ndk-r9b-windows-x86\platforms\android-13\arch-arm -fPIE -c pt_lock.c

@echo "2. build exec file"

@Rem pie flag is used in linking stage.
D:\android-ndk-r9b-windows-x86\toolchains\arm-linux-androideabi-4.6\prebuilt\windows\bin\arm-linux-androideabi-gcc.exe --sysroot=D:\android-ndk-r9b-windows-x86\platforms\android-13\arch-arm -pie -o pt_lock pt_lock.o

@pause

