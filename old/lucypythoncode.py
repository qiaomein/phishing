import csv, math

filename = 'lucy.csv'

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

xlist = []
ylist = []
with open(filename,'r') as csvfile: # go through the csvfile
    line = csv.reader(csvfile)
    for i in line:
        xlist.append(int(i[0])) #make the lists
        ylist.append(int(i[1]))

print('ENTROPY:',findEntropy(xlist,ylist))
