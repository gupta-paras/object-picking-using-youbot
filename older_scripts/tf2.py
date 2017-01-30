# In the name of GOD //

# program for extimation of the transformation matrix

# res will transform x,y,z = u, v, w


import numpy as np
x = np.array([1,2], dtype=np.float64);
y = np.array([3,8], dtype=np.float64);
z = np.array([3.7,4], dtype=np.float64);
u = np.array([3,4.9], dtype=np.float64);
v = np.array([3.2,4], dtype=np.float64);
w = np.array([3,4.878], dtype=np.float64);

# read numpy arrays

xx = x*x;
xy = x*y;
xz = x*z;

yy = y*y;
yz = y*z;
zz = z*z;

print zz

def calc_inv(p):
	px = p*x; py = p*y; pz = p*z;
	A = np.array([[np.sum(xx), np.sum(xy), np.sum(xz)],[np.sum(xy), np.sum(yy), np.sum(yz)],[np.sum(xz), np.sum(yz), np.sum(zz)]])
	b = np.array([np.sum(px), np.sum(py), np.sum(pz)]);
	inv_A = np.linalg.inv(A)
	res = np.dot(inv_A, b)
	return res;


res = []
res.append(calc_inv(u))
res.append(calc_inv(v))
res.append(calc_inv(w))
res = np.array(res)

print res


# (u, v, w) = res * (x,y,z)