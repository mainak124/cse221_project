import numpy as np
import matplotlib.pyplot as plt

def plot():
	p_list = [16, 32, 64, 128, 256]
	p, x_, y = np.loadtxt("mem_latency.txt", delimiter=",", unpack=True)
	x = np.log(x_)/np.log(2)
	for p_ in  p_list:
		x1 = [a for a,b in zip(x, p) if b==p_]
		y1 = [a for a,b in zip(y, p) if b==p_]
		print p, x1, y1
		plt.plot(x1, y1)
	plt.ylabel("Memory Access Latency")
	plt.xlabel("Log Array Size")
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

l1_cache=0
l2_cache=8192
memory=65536

print "For L1:"
getAvg(l1_cache, l2_cache)
print "For L2:"
getAvg(l2_cache, memory)
print "For Main Memory:"
getAvg(memory, 100000000000000000000000)
