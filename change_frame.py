import numpy as np

def get_sum(x):
	res = 0.0;
	for e in x:
		res = res + e
	return res;

def get_regression (f, x, y, z):	# this function will give a row vector of size (1*4) for transforming the x, y 
	res = []
	xx = x*x; xy = x*y; xz = x*z
	yy = y*y; yz = y*z
	zz = z*z
	fx = f*x; fy = f*y; fz = f*z

	xx = get_sum(xx);	yy = get_sum(yy);	zz = get_sum(zz)
	xy = get_sum(xy);	xz = get_sum(xz);	yz = get_sum(yz)
	fx = get_sum(fx);	fy = get_sum(fy);	fz = get_sum(fz)

	l = len(x)	# sum of column of ones
	x = get_sum(x);	y = get_sum(y);	z = get_sum(z);	f = get_sum(f)

	A = [ [xx, xy, xz, x], [xy, yy, yz, y], [xz, yz, zz, z], [x, y, z, l] ];
	b = [fx, fy, fz, f];
	A = np.array(A)
	b = np.array(b)

	res = np.linalg.solve(A,b)
	return res

x = [1,2,3,4, 5, 6, 7];
y = [3,6,2,6, 2, 6, 1];
z = [9,3,0,6, 1, 2, 3];

u = [ 0.63619546, 8.68654264,  3.66500888,  7.46451432, 9, 7, 2];
v = [1,2,3,4, 5, 6, 7];
w = [8,8,8,8,8,8,8];

x = np.array(x);	y = np.array(y);	z = np.array(z);	
u = np.array(u);	v = np.array(v);	w = np.array(w);

transformation_matrix = [get_regression(u, x, y, z), get_regression(v, x, y, z), get_regression(w, x, y, z)]

# read x, y, z & u, v, w from the files and write the transformation_matrix to some file