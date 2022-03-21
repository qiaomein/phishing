import numpy as np
import pandas as pd
from statistics import *
import csv
from matplotlib import pyplot as plt
#from sklearn.datasets.samples_generator import make_blobs
from sklearn.cluster import KMeans

## plot first trajectory
filename = 'positions.csv'
runner = []
u = []
i = 8 # must be even number from 0 to 8
with open(filename, newline = '') as csvfile:
    csvread = csv.reader(csvfile)
    for row in csvread:
        if len(row) > 1:
            #print(row)
            runner.append([row[6],row[7]])
            u.append([row[i],row[i+1]])
            
        if row == ['2']:
            break

#print(runner)
plt.figure()
plt.plot([u[i][0] for i in range(len(u))],[u[i][1] for i in range(len(u))],'.')

plt.plot([runner[i][0] for i in range(len(runner))],[runner[i][1] for i in range(len(runner))],'.')
plt.axis('off')
plt.show()