OBJS = main.o funzioni.o entropy.o crittografia.o file.o gen_psw.o struttura_dati.o
EXNAME = pswManager
CXXFLAGS = -Wall `pkg-config --cflags gtk+-3.0` #-D NDEBUG
LDFLAGS = -export-dynamic `pkg-config --libs gtk+-3.0` -lcrypto
LIBS = -ldl

.PHONY: dependencies clean cleanAll debug

compile: dependencies $(OBJS)
	g++ -o $(EXNAME) $(OBJS) $(LDFLAGS) $(LIBS)

-include depend.txt

dependencies:
	g++ -MM *.cc > depend.txt

clean:
	rm -f *.o *~

removeFile:
	rm -rf *.txt

cleanAll: clean removeFile
	rm -f $(EXNAME)
