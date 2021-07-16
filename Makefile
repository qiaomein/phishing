PROG = output
CFLAGS = -g -Wall

CPP_FILES = entropy.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}
#CPP_FILES = random_chasing.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}
#CPP_FILES = test.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}


all : ${PROG};

${PROG} :
	-g++ ${CFLAGS} -o ${PROG} ${CPP_FILES}
#	-"H:\Program Files\MATLAB\R2020b\bin\matlab.exe" -nodisplay -nosplash -nodesktop -r "run('C:\Users\Jack Qiao\OneDrive\Desktop\Research\HSMC 21\phishing\data_analysis.m'); exit;"
clean:
	-del ${PROG} *.o *.exe *.csv