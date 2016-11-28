import numpy as np
import matplotlib.pyplot as plt

def plot():
	x, y = np.loadtxt("fileCacheSize.txt", delimiter=",", unpack=True)
	x = x/1000000
	plt.plot(y, x)
	plt.ylabel("File Read Latency")
	plt.xlabel("Read Buffer Size")
	plt.show()

def getAvg(lower, upper):
	p_list = [16, 32, 64, 128, 256]
	p, x_, y = np.loadtxt("pagefault.txt", delimiter=",", unpack=True)
	# x = np.log(x_)/np.log(2)
	memaccess=[]
	bigarr=[]
	for p_ in  p_list:
		memarr = [(float(b)/(100000)) for a,b,c in zip(x_,y,p) if c==p_ and a>lower and a<=upper]
		bigarr = bigarr+memarr
		memaccess.append(np.mean(memarr))
	# print np.mean(memaccess)
	print np.mean(bigarr)
	print np.std(bigarr)#/np.mean(bigarr)

plot()
