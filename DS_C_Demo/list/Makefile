obj = main.o list-app.o
bin_name = main

$(bin_name) : $(obj)
	gcc -o main $(obj)

main.o : main.c list-app.h
	gcc -c main.c

list-app.o : list-app.c list-app.h
	gcc -c list-app.c

.PHONY : clean
clean :
	-rm $(bin_name) $(obj)  # 减号表示也许某些文件出现问题，但不要管继续做后面事情。

