prefix=dlist
obj = main.o $(prefix)-app.o
bin_name = main

$(bin_name) : $(obj)
	gcc -o main $(obj)

main.o : main.c $(prefix)-app.h
	gcc -c main.c

$(prefix)-app.o : $(prefix)-app.c $(prefix)-app.h
	gcc -c $(prefix)-app.c

.PHONY : clean
clean :
	-rm $(bin_name) $(obj)

