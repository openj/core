CFLAGS=$(COMP)

libj : $(LIBJ_OBJS)
	cc  $(LIBJ_OBJS) $(SOLINK)

jconsole : jconsole.o jeload.o
	cc  jconsole.o jeload.o $(JCON_LINK) $(M32) $(LIBREADLINE) -o jconsole

tsdll : tsdll.o
	cc tsdll.o $(SOLINK)
