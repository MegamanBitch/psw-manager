OBJS = main.o funzioni.o gen_chiavi.o
CXXFLAGS = -g -Wall `pkg-config --libs --cflags gtk+-3.0` `pkg-config --cflags --libs glib-2.0`

Compile: dependencies $(OBJS)
	g++ -o PswManager $(OBJS)

-include depend.txt

dependencies:
	g++ -MM *.cc > depend.txt

CleanAll:
	rm -f *.o
