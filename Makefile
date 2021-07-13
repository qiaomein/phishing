PROG = output
CFLAGS = -g -Wall

CPP_FILES = entropy.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}
#CPP_FILES = random_chasing.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}

all : ${PROG};

${PROG} :
	-g++ ${CFLAGS} -o ${PROG} ${CPP_FILES}
	-
clean:
	-del ${PROG} *.o *.exe *.csv