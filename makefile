CFLAGS=$(COMP)
CXXFLAGS=$(COMP)

libj : $(LIBJ_OBJS) $(LIBJ_WIN_OBJS) $(LIBJ_WINOLE_OBJS) $(LIBJ_JJNI_OBJS)
	${CXX} $(LIBJ_OBJS) $(LIBJ_WIN_OBJS) $(LIBJ_WINOLE_OBJS) $(LIBJ_JJNI_OBJS) $(LIBJDEF) $(SOLINK)

jconsole : jconsole.o jeload.o
	${CC} jconsole.o jeload.o $(LIBREADLINE) $(JCONLINK) -o jconsole

tsdll : tsdll.o
	${CC} tsdll.o $(LIBTSDEF) $(TSLINK)

clean :
	rm -f *.o win/*.o *.dll *.so jconsole *.x *.jmf

.PHONY : clean
