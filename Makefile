DESTDIR?=
PREFIX?=	/usr/local

CFLAGS+=	-Wall -Wextra

OBJ=		cmdsh.o main.o
OBJ.test=	cmdsh.o test.o

all: cmdsh test

check: all
	./test

install: all
	install -d ${DESTDIR}${PREFIX}/bin
	install -m755 cmdsh ${DESTDIR}${PREFIX}/bin/
	@echo "NOTE: don't forget to add ${PREFIX}/bin/cmdsh to /etc/shells"

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/cmdsh
	@echo "NOTE: don't forget to remove ${PREFIX}/bin/cmdsh from /etc/shells"

clean:
	rm -f cmdsh test *.o

cmdsh: ${OBJ}
	${CC} ${LDFLAGS} -o cmdsh ${OBJ} ${LDLIBS}

test: ${OBJ.test}
	${CC} ${LDFLAGS} -o test ${OBJ.test} ${LDLIBS}

cmdsh.o: cmdsh.h
main.o:  cmdsh.h
test.o:  cmdsh.h

.PHONY: all check install uninstall clean
