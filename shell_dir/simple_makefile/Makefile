RM = rm

CFLAGS = -g -Wall -O

TARGET = stl_app

fname = stl_memory_test

XX = g++

OBJS = $(fname).o

$(TARGET) : $(OBJS)
	$(XX) $(CFLAGS) -o $(TARGET) $(OBJS)
	chmod +x $(TARGET)

$(fname).o : $(fname).cpp
	$(XX) $(CFLAGS) -c $(fname).cpp

#  target build必须先于*.o之前，此处会失败！
#$(TARGET) : $(OBJS)
#	$(XX) $(CFLAGS) -o $(TARGET) $(OBJS)

.PHONY: clean

clean:
	$(RM) $(OBJS) $(TARGET)

