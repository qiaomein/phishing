PROG = output
CFLAGS = -g -Wall

CPP_FILES = stationary_chasing.cpp bresenham.cpp #${wildcard *cpp}

all : ${PROG};

${PROG} :
	-g++ ${CFLAGS} -o ${PROG} ${CPP_FILES}

clean:
	-del ${PROG} *.o *.exe *.csv