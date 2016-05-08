OBJS = main.o funzioni.o gen_chiavi.o
<<<<<<< HEAD
EXNAME = PswManager
CXXFLAGS =-Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS=-export-dynamic `pkg-config --libs gtk+-3.0`

.PHONY: dependencies clean cleanAll

compile: dependencies $(OBJS)
	g++ -o $(EXNAME) $(OBJS) $(LDFLAGS)
=======
CXXFLAGS = -g -Wall `pkg-config --libs --cflags gtk+-3.0` `pkg-config --cflags --libs glib-2.0`

Compile: dependencies $(OBJS)
	g++ -o PswManager $(OBJS)
>>>>>>> 8a1bc59a4216be727978adc6db9a5abfed9a1c2c

-include depend.txt

dependencies:
	g++ -MM *.cc > depend.txt

<<<<<<< HEAD
clean:
	rm -f *.o *~

cleanAll: clean
	rm -f $(EXNAME)
=======
CleanAll:
	rm -f *.o
>>>>>>> 8a1bc59a4216be727978adc6db9a5abfed9a1c2c
