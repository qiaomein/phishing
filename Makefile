PROG = output
CFLAGS = -g -Wall

PY_FILES = plotting.py
CPP_FILES = run.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}
#CPP_FILES = entropy.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}
#CPP_FILES = random_chasing.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}
#CPP_FILES = dynamic_following.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}
#CPP_FILES = test.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}


all : ${PROG};

${PROG} :
	-g++ ${CFLAGS} -o ${PROG} ${CPP_FILES}
	-./output
	-python ${PY_FILES}
#	-"H:\Program Files\MATLAB\R2020b\bin\matlab.exe" -nosplash -nodesktop -r "run('C:\Users\Jack Qiao\OneDrive\Desktop\Research\HSMC 21\phishing\clustering.m');"
clean:
	-del ${PROG} *.o *.exe *.csv