import statistics
import csv
import math
from matplotlib import pyplot as plt

def findEntropy(xlist,ylist):
    plist = [0]*9
    tsteps = len(xlist)
    for i in range(1,len(xlist)-1):
        xold = xlist[i-1]
        yold = ylist[i-1]
        x = xlist[i]
        y = ylist[i]
        dx = x-xold
        dy = y-yold

        if dx == 1:
            if dy == 1:
                plist[0] += 1
            elif dy == -1: plist[1] += 1
            else: plist[2] += 1
        elif dx == -1:
            if dy == 1:
                plist[3] += 1
            elif dy == -1: plist[4] += 1
            else: plist[5] += 1
        else:
            if dy == 1: plist[6]+=1
            elif dy == -1: plist[7] += 1
            else: plist[8] += 1
    H = 0
    for p in plist:
        P = p/tsteps
        if P == 0: continue
        H += P*math.log2(1/P)
    return H


def findEntropyBuffer(buffersize,traj,prop = 1):
    l = len(traj)//2
    s = 0; counter = 0
    for i in range(int(l*prop)-buffersize): #iterate over buffers
        counter += 1
        x = traj[i:2*(i+buffersize):2]
        y = traj[i+1:2*(i+1+buffersize):2]
        e = findEntropy(x,y)
        s += e
    return s/counter

filename = 'trajectories.csv'



thresholds = []
with open('thresholds.csv') as csvfile: # change threshold file depending on what thresholds we are using
    csvread = csv.reader(csvfile)
    for line in csvread:
        thresholds.extend([float(x) for x in line])
print(f'Thresholds: {thresholds}')

buffersize = 128
prop = .1

with open(filename) as csvfile:
    csvread = csv.reader(csvfile)

    c = [0]*3
    r = [0]*3
    f = [0]*3
    error = []
    for line in csvread: #iterate over trajectories
        traj = line[1:-2]
        traj = [int(x) for x in traj]
        activity = line[0]
        e = findEntropyBuffer(buffersize,traj,prop)
        
        
        if e < thresholds[1] and e > 0:
            #print(f'Chasing: {e}')
            c[0]+=1
            if activity == 'chasing':
                c[1]+=1
            else:
                c[2] += 1
                error.append([f'Boat is {activity} instead of chasing'])
        elif e < thresholds[2]:
            #print(f"Following: {e}")
            f[0]+=1
            if activity == 'following':
                f[1]+= 1
            else:
                f[2]+=1
                error.append([f'Boat is {activity} instead of following'])
        elif e > thresholds[2]:
            r[0]+=1
            if activity == 'random walk':
                r[1]+=1
            else:
                r[2] += 1
                error.append([f'Boat is {activity} instead of random walking'])
            #print(f"Random walk: {e}")
    with open(f'detection{prop}.csv','w',newline='') as csvfile:
        csvwrite = csv.writer(csvfile)
        csvwrite.writerows([c,f,r])
        csvwrite.writerow(['ERROR LOG:'])
        csvwrite.writerows(error)


        csvwrite.writerow(['Accuracy: '])
        csvwrite.writerow([c[1]/c[0],f[1]/f[0],r[1]/r[0]])



    




