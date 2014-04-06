# 递归搜索所有目录下文件
# SRCS = $(call rwildcard, ./, *.c *.cpp)
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CC = gcc

XX = g++

CFLAGS = -Wall -O -g

TARGET = main     # 变量定义类似c中宏

INCDIR = -I"./header"

LIBDIR = -L"/usr/local/lib"

LIBS = ""

RM = -rm -rf

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

SRCS = $(call rwildcard, ./, *.c)   # 只搜索c文件

OBJS = $(patsubst %.c,%.o,$(SRCS))

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(INCDIR) $(LIBDIR) $(LIBS) 
	echo $(SRCS)

.PHONY : clean
clean:
	$(RM) $(OBJS) $(TARGET)

