#!/usr/local/pyenv/shims/python
import random

MAX_N = 100000
MAX_W = 1000
seq = 0
RANDOMCASE_NUMS = 10

class unionfind:
	def __init__ (self,n):
		self.data = [-1] * n

	def find(self, a):
		if self.data[a] < 0:
			return a;
		else:
			self.data[a] = self.find(self.data[a])
			return self.data[a]
	
	def marge(self,a,b):
		a = self.find(a)
		b = self.find(b)
		if a == b:
			return
		if a < b: 
			a,b = b,a
		self.data[a] += self.data[b]
		self.data[b] = a
	
	def size(self,a):
		return -self.data[self.find(a)]

class Tree:
	def __init__ (self,n):
		self.edge = []
		self.N = n
		self.graph = unionfind(self.N)

	def randomCreate(self):
		elist = range(self.N)
		while self.graph.size(0) < self.N:
			used = [0] * self.N
			for i in elist:
				if used[i] == 0:
					while 1:
						a = elist[random.randrange(0,len(elist))]
						if a != i:
							break
					used[a] = 1
					self.add_edge(a,i)
			temp = []
			for i in elist:
				if self.graph.find(i) == i:
					temp.append(i)
			elist = temp

	def add_edge(self, a, b ):
		self.edge.append( (a,b) )
		self.graph.marge(a,b)

	def get(self,a):
		return self.edge[a]


def Generate(N, w_min = 0):
	global seq
	filename = '%02d_random_%02d.in' % (1, seq)
	tree = Tree(N)
	tree.randomCreate()
	with open(filename, 'w') as f:
		print >> f, str(N)
		for i in xrange(N-1):
			edgee = tree.get(i)
			print >> f, "%d %d" % (edgee[0]+1,edgee[1]+1)
	seq += 1
if __name__ == '__main__':
        for i in xrange(20):
                Generate(MAX_N)
