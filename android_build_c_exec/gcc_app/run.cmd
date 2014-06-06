@echo "1. build .o file"

D:\android-ndk-r9b-windows-x86\toolchains\arm-linux-androideabi-4.6\prebuilt\windows\bin\arm-linux-androideabi-gcc.exe --sysroot=D:\android-ndk-r9b-windows-x86\platforms\android-13\arch-arm -c main.c

@echo "2. build exec file"

D:\android-ndk-r9b-windows-x86\toolchains\arm-linux-androideabi-4.6\prebuilt\windows\bin\arm-linux-androideabi-gcc.exe --sysroot=D:\android-ndk-r9b-windows-x86\platforms\android-13\arch-arm -o main_exec main.o

@pause

