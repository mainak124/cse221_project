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

def getAvg():
	p = np.loadtxt("pagefault.txt")
	print np.mean(p)
	print np.std(p)

getAvg()
