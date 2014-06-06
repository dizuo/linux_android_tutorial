prefix=lru-cache
extern_o=dlist-app.o
extern_c=../dlist/dlist-app.c

obj = main.o $(prefix)-app.o $(extern_o)
bin_name = main

$(bin_name) : $(obj)
	gcc -o main $(obj)

main.o : main.c $(prefix)-app.h
	gcc -c main.c

$(prefix)-app.o : $(prefix)-app.c $(prefix)-app.h
	gcc -c $(prefix)-app.c $(extern_c)

.PHONY : clean
clean :
	-rm $(bin_name) $(obj)

