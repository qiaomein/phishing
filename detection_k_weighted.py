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

weighted_thresholds = []
with open('weighted_thresholds.csv') as csvfile: # change threshold file depending on what thresholds we are using
    csvread = csv.reader(csvfile)
    for line in csvread:
        weighted_thresholds.append([float(x) for x in line])


print(f'Weighted Means Thresholds: {weighted_thresholds}')

voronoi_thresholds = []
with open('voronoi_thresholds.csv') as csvfile: # change threshold file depending on what thresholds we are using
    csvread = csv.reader(csvfile)
    for line in csvread:
        voronoi_thresholds.append([float(x) for x in line])
print(f'K means Voronoi Thresholds: {voronoi_thresholds}')


buffersize = 128
prop = .1
timesteps = 3000


randtraj = []
chasetraj = []
foltraj = []
# get following trajectories real quick

with open("trajectories_following.csv") as csvfile:
    csvread = csv.reader(csvfile)

    for line in csvread:
        if len(line) > 1:
            foltraj.extend([int(x) for x in line[:2]])

with open(filename) as csvfile:
    csvread = csv.reader(csvfile)

    for line in csvread: #iterate over trajectories
        if len(line)>1:
            randtraj.extend([int(x) for x in line[:2]])
            chasetraj.extend([int(x) for x in line[2:4]])


# randtraj, chasetraj, foltraj all list of coordinate pairs



n = len(foltraj)//timesteps//2
print(f'{n} trajectories')


error_d = {'r':0,'c':0,'f':0}

with open(f'detection_k_weighted_p{prop}.csv','w',newline='') as csvfile:
    csvwrite = csv.writer(csvfile)


    for i in range(n): # looping through all trajectories
        e = {'r':findEntropyBuffer(buffersize,randtraj[i*timesteps:(i+1)*timesteps],prop),
        'c':findEntropyBuffer(buffersize,chasetraj[i*timesteps:(i+1)*timesteps],prop),
        'f':findEntropyBuffer(buffersize,foltraj[i*timesteps:(i+1)*timesteps],prop)}
        
        
        # detection/comparison for voronoi
        thresholds = weighted_thresholds[2]

        t1,t2,t3 = thresholds
        for key in e: #loop through r,c,f
            z = e[key] 
            if z > t1 and z <= t2:
                category = 'chasing'
            elif z > t2 and z <= t3:
                category = 'following'
            elif z > t3:
                category = 'random walk'
            
            if key[0] != category[0]: # if classification is wrong
                error = f'Boat is {key} instead of {category}'
                csvwrite.writerow([error])
                error_d[key] += 1
            else: # if classify correctly
                pass


    r_error = error_d['r']/n*100
    c_error = error_d['c']/n*100
    f_error = error_d['f']/n*100

    csvwrite.writerows(error_d.items())
    csvwrite.writerows([['\nAccuracy (%): '],[f"randomwalk: {100-r_error}"],[f"chasing: {100-c_error}"],[f"following: {100-f_error}"]])








