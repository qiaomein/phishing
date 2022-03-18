PROG = output
CFLAGS = -g -Wall

PY_FILES = plotting.py
#CPP_FILES = entropy.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}
#CPP_FILES = random_chasing.cpp randomwalk.cpp bresenham.cpp #${wildcard *cpp}
#CPP_FILES = dynamic_following.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}
#CPP_FILES = classification_set.cpp randomwalk.cpp bresenham.cpp 

#use this line for training
#CPP_FILES = training.cpp randomwalk.cpp bresenham.cpp following.cpp #${wildcard *cpp}

#use this line ONCE done training (creates a new set to run detection/classification on)
CPP_FILES = classification_set.cpp randomwalk.cpp bresenham.cpp following.cpp

# for generating RW-chasing csv
#CPP_FILES = RW-Chasing.cpp randomwalk.cpp bresenham.cpp following.cpp

all : ${PROG};

${PROG} :
#compiles cpp code 
	-g++ ${CFLAGS} -o ${PROG} ${CPP_FILES} 
#runs the exe file
	-./output
#runs python files in PY_FILES
	-python ${PY_FILES}
#	-"H:\Program Files\MATLAB\R2020b\bin\matlab.exe" -nosplash -nodesktop -r "run('C:\Users\Jack Qiao\OneDrive\Desktop\Research\HSMC 21\phishing\clustering.m');"
clean:
	-del ${PROG} *.o *.exe *.csv