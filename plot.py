import numpy as np
import matplotlib.pyplot as plt

"""
    Abgabe Blatt 5 Aufgabe 11
    Niklas Rausch, Anne Schulte-Kroll und Wolf Weber
"""

datas = []
datas.append( np.loadtxt("h_t=0.005.csv", delimiter=";") )
datas.append( np.loadtxt("h_t=0.01.csv", delimiter=";")  )

legends=[]
fig = plt.figure() # figsize=(11,6)
for di in range(len(datas)):
    data = datas[di]
    t = np.transpose(data)[0]
    x = np.linspace(-1,1, len(data[0][1:]))
    i=0
    while(i < len(data)):
        col1 = float(len(data)-i+1)/(1.2*len(data))
        mcolor=(col1,col1,1)
        if di==1:
            mcolor=(1,col1,col1)
        if i == 0:
            mcolor=(0,0,0)

        plt.plot(x, data[i][1:], '-', color=mcolor)
        legends.append(str(di)+") t="+str(t[i]))
        i = i+1

plt.legend(legends, ncol=6, bbox_to_anchor=(0, 1, 1, 0), loc="lower left", mode="expand")
plt.xlabel("x")
plt.ylabel("u(x,t)")
plt.grid(True)
fig.show()

######

for di in range(len(datas)):
    data = datas[di]
    t = np.transpose(data)[0]
    #x = np.linspace(-1,1, len(data[0][1:]))
    h_x = 0.2
    x = np.arange(-1-h_x/2, 1+h_x, h_x)
    pltdata = np.delete(data,obj=0,axis=1) # delete first column with times (axis=1 for column)

    fig = plt.figure() # figsize=(11,6)
    contourplot = plt.pcolormesh(x,t,pltdata)
    fig.colorbar(contourplot)
    # plt.grid(True)
    plt.xlabel("x")
    plt.ylabel("t")
    # TODO:
    #plt.title(mfile+"\nfinal function u(x,y)\n(N+2)x(N+2) grid with sample points (i,j)\nincluding boundary condition")
    fig.show()


# hold program open
input()