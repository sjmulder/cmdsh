CFLAGS+=	-Wall -Wextra

OBJ=		cmdsh.o main.o
OBJ.test=	cmdsh.o test.o

all: cmdsh test

check: all
	./test

clean:
	rm -f cmdsh test *.o

cmdsh: ${OBJ}
	${CC} ${LDFLAGS} -o cmdsh ${OBJ} ${LDLIBS}

test: ${OBJ.test}
	${CC} ${LDFLAGS} -o test ${OBJ.test} ${LDLIBS}

cmdsh.o: cmdsh.h
main.o:  cmdsh.h
test.o:  cmdsh.h

.PHONY: all check clean
