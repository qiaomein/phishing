import numpy as np
import pandas as pd
from statistics import *
import csv
from matplotlib import pyplot as plt
#from sklearn.datasets.samples_generator import make_blobs
#from sklearn.cluster import KMeans

print('python script ran')

### TESTING ###
#X, y = make_blobs(n_samples=300, centers=8, cluster_std=0.60, random_state=0)
#x = X[:,0]; y = X[:,1];
#plt.plot(x,y)
###############

filename = "entropies.csv"

randomwalk = []
chasingwalk = []
followingwalk = []
runnerwalk = []

with open(filename, newline ='') as csvfile:
    csvread = csv.reader(csvfile)
    for traj in csvread:
        #print(positions)
        randomwalk.append(float(traj[0].strip()))
        chasingwalk.append(float(traj[1].strip()))
        followingwalk.append(float(traj[2].strip()))
                

#plt.scatter(randomwalk[::2],randomwalk[1::2])
#print(followingwalk)

plt.figure(figsize=(18,9))

plt.subplot(121)
plt.plot(followingwalk,[0]*len(followingwalk),'ro',markersize = 2)

plt.plot(randomwalk,[0]*len(followingwalk),'bo',markersize = 2)

plt.plot(chasingwalk,[0]*len(followingwalk),'go',markersize = 2)
#plt.xlim(0,4)

data = [randomwalk,chasingwalk,followingwalk]
means = [mean(l) for l in data]
stdevs = [stdev(l) for l in data]
print(means)
print(stdevs)

plt.plot(means,[0]*3,'yo',markersize=5)


## writing to csv file
thresholds = [0,means[2]-4*stdevs[2],means[2]+stdevs[2]*(means[0]-means[2])/(stdevs[0]+stdevs[2])]
with open('thresholds.csv','w') as csvfile:
    csvwriter = csv.writer(csvfile)

    csvwriter.writerow(thresholds)




for x in thresholds:
    plt.axvline(x)

plt.subplot(122)

plt.hist(chasingwalk,bins = 50)
plt.hist(randomwalk,bins = 50)
plt.hist(followingwalk,bins = 50)



plt.show()

