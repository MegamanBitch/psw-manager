OBJS = main.o funzioni.o entropy.o crittografia.o file.o gen_psw.o
EXNAME = pswManager
CXXFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS = -export-dynamic `pkg-config --libs gtk+-3.0` -lcrypto
LIBS = -ldl

.PHONY: dependencies clean cleanAll

compile: dependencies $(OBJS)
	g++ -o $(EXNAME) $(OBJS) $(LDFLAGS) $(LIBS)

-include depend.txt

dependencies:
	g++ -MM *.cc > depend.txt

clean:
	rm -f *.o *~ *.dat

cleanAll: clean
	rm -f $(EXNAME)
