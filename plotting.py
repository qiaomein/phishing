import numpy as np
import pandas as pd
from statistics import *
import csv
from matplotlib import pyplot as plt
#from sklearn.datasets.samples_generator import make_blobs
from sklearn.cluster import KMeans

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
plt.title('Entropy Clusters')



plt.plot(randomwalk,[0]*len(followingwalk),'bo',markersize = 2)

plt.plot(chasingwalk,[0]*len(followingwalk),'go',markersize = 2)
plt.plot(followingwalk,[0]*len(followingwalk),'ro',markersize = 2)

#plt.xlim(0,4)
plt.legend(['random','chasing','following'])
data = [randomwalk,chasingwalk,followingwalk]

DATA = np.array(randomwalk+chasingwalk+followingwalk)
k_means = KMeans(n_clusters = 3).fit(DATA.reshape(-1,1))
k_clusters = sorted([float(x) for x in k_means.cluster_centers_])
print(f"K-means cluster: {k_clusters}")

means = [mean(l) for l in data]
stdevs = [stdev(l) for l in data]
print("Supervised means, stdevs: ",means,"|||",stdevs)

plt.plot(means,[0]*3,'yo',markersize=5)


## writing to csv file
thresholds = [0,means[1]+stdevs[1]*(means[2]-means[1])/(stdevs[2]+stdevs[1]),means[2]+stdevs[2]*(means[0]-means[2])/(stdevs[0]+stdevs[2])]
voronoi_thresholds = [0,(k_clusters[0]+k_clusters[1])/2,(k_clusters[2]+k_clusters[1])/2]

print("THRESHOLDS:", thresholds); print(voronoi_thresholds)

with open('thresholds.csv','w') as csvfile:
    csvwriter = csv.writer(csvfile)

    csvwriter.writerow(thresholds)

for i in range(len(thresholds)):
    plt.axvline(thresholds[i])
    plt.axvline(voronoi_thresholds[i],color = 'red')

plt.subplot(122)
plt.title('Distributions')


plt.hist(randomwalk,bins = 50)
plt.hist(chasingwalk,bins = 50)
plt.hist(followingwalk,bins = 50)

plt.legend(['random','chasing','following'])



plt.show()

