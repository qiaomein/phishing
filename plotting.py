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

def weighted_t(m1,s1,m2,s2):
    return m1 + (s1*(m2-m1))/(s1+s2)


histogram_resolution = 10

filename = "entropies.csv"


#### plotting entropy clusters #####

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
        #followingwalk.append(float(traj[2].strip()))

with open('entropies_fol.csv',newline = '') as csvfile:
    csvread = csv.reader(csvfile)
    for traj in csvread:
        followingwalk.append(float(traj[0].strip()))   

#plt.scatter(randomwalk[::2],randomwalk[1::2])
#print(followingwalk)

plt.figure(figsize=(18,9))

plt.title('Entropy Clusters')




plt.plot(randomwalk,[0]*len(followingwalk),'bo',markersize = 2)

plt.plot(chasingwalk,[0]*len(followingwalk),'go',markersize = 2)
plt.plot(followingwalk,[0]*len(followingwalk),'ro',markersize = 2)

#plt.xlim(0,4)

#########################

data = [randomwalk,chasingwalk,followingwalk]
DATA = np.array(randomwalk+chasingwalk+followingwalk)
k_means = KMeans(n_clusters = 3).fit(DATA.reshape(-1,1))
k_clusters = sorted([float(x) for x in k_means.cluster_centers_])
print(f"K-means cluster: {k_clusters}")

means = [mean(l) for l in data]
stdevs = [stdev(l) for l in data]
d = {means[i]:stdevs[i] for i in range(len(data))}
#print(d)
d = sorted(d.items())# d is sorted by key list of tuples
#print(d)

print("Supervised means: stdevs: ", d)

plt.plot(means,[0]*3,'yo',markersize=10)
plt.plot(k_clusters,[0]*3,'mo',markersize = 10)



## writing to csv file

supervised_weighted_thresholds = [0] + [weighted_t(d[i][0],d[i][1],d[i+1][0],d[i+1][1]) for i in range(len(d)-1)]

k_weighted_thresholds = [0] + [weighted_t(k_clusters[i],d[i][1],k_clusters[i+1],d[i+1][1]) for i in range(len(d)-1)]
# same stdev?


k_voronoi_thresholds = [0,(k_clusters[0]+k_clusters[1])/2,(k_clusters[2]+k_clusters[1])/2]
supervised_voronoi_thresholds = [0] + [(d[i][0]+d[i+1][0])/2 for i in range(len(d)-1)]

#print("")

with open('weighted_thresholds.csv','w') as csvfile:
    csvwriter = csv.writer(csvfile)

    csvwriter.writerow(supervised_weighted_thresholds)
    csvwriter.writerow(k_weighted_thresholds)

with open('voronoi_thresholds.csv','w') as csvfile:
    csvwriter = csv.writer(csvfile)

    csvwriter.writerow(supervised_voronoi_thresholds)
    csvwriter.writerow(k_voronoi_thresholds)

for i in range(len(d)):
    plt.axvline(supervised_weighted_thresholds[i], color = 'purple')
    plt.axvline(supervised_voronoi_thresholds[i],color = 'red')
    plt.axvline(k_voronoi_thresholds[i],color = 'blue')
    plt.axvline(k_weighted_thresholds[i],color = 'green')


plt.legend(['random','chasing','following','supervised means','k-means','supervised weighted t','supervised voronoi t','k voronoi t'],loc='best',framealpha = 1)

plt.show()


plt.figure()
plt.title('Distributions')


plt.hist(randomwalk,bins = histogram_resolution)
plt.hist(chasingwalk,bins = histogram_resolution)
plt.hist(followingwalk,bins = histogram_resolution)

plt.legend(['random','chasing','following'])



plt.show()

