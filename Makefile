OBJS = main.o funzioni.o gen_chiavi.o entropy.o
EXNAME = pswManager
CXXFLAGS =-Wall `pkg-config --cflags gtk+-3.0` -lcryptopp
LDFLAGS=-export-dynamic `pkg-config --libs gtk+-3.0`

.PHONY: dependencies clean cleanAll

compile: dependencies $(OBJS)
	g++ -o $(EXNAME) $(OBJS) $(LDFLAGS)

-include depend.txt

dependencies:
	g++ -MM *.cc > depend.txt

clean:
	rm -f *.o *~

cleanAll: clean
	rm -f $(EXNAME)
