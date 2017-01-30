// In the name of the Mighty God //

// Title : Reduced closed form inverse kinamatics

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define pi 3.14159

typedef long double ld;


ld get_angle(ld x, ld y){
	ld res = atan(y/x);
	if(x<0)	res+=pi;
	if(res<0)	res+=2*pi;
	return res;
}

ld get_radius(ld x, ld y){
	return sqrt(x*x + y*y);
}

pair<ld, ld> get_pair_angles(ld r, ld l1, ld l2){
	cout<<l1<<' '<<l2<<' '<<r<<endl;

	ld mn = 0, mx = pi/2;
	for(int i=0;i<20;i++){
		ld theta1 = (mx+mn)/2;
		if(sin(theta1) * l1 / l2 >= 1)	{	mx = 0.98 * asin(l2/l1);	continue;	}
		ld theta2 = asin(sin(theta1) * l1 / l2);
		ld cur = l1*cos(theta1) + l2 * cos(theta2);
		if(cur<r)	mx = theta1;
		else mn = theta1;
	}

	ld theta1 = mn;
	ld theta2 = asin(sin(theta1) * l1 / l2);

	theta1 = (l1*l1 + r*r - l2*l2)/(2*l1*r);
	theta1 = acos(theta1);

	theta2 = (l2*l2 + r*r - l1*l1)/(2*l2*r);
	theta2 = acos(theta2);




	return make_pair(theta1, theta2);
}

vector<ld> change_frame(std::vector<ld> &v, ld l[]) {	// v[1..3] x,y,z; v[4] : theta; z[5] radius ;
	ld theta1 = get_angle(v[2], v[1]);
	ld r = get_radius(v[1], v[2]);
	ld z = v[3];
	ld z_ = l[4] + z;
	ld r_ = get_radius(r,z_);
	ld offset_angle = get_angle(r, z_);
	pair<ld, ld> foo = get_pair_angles(r_, l[2], l[3]);

	std::vector<ld> res(7);
	res[1] = theta1;
	res[2] = foo.first + offset_angle;
	cout<<res[2]<<endl;
	res[3] = -pi - foo.first - foo.second;
	res[4] = foo.second + pi/2 - offset_angle;
	res[5] = v[4] - theta1;
	if(res[5]<0)	res[5] += pi;
	res[6] = 2 * v[5];

	cout<<foo.first<<' '<<foo.second<<endl;

	return res;
}

int main(){
	ld offset_angles[] = {0, 0, pi/2 - 1.04883, 2.43523 - pi, pi - 1.7318, 0, 0, 0 };

            ld link_lengths[] = {0,0,155, 135, 218 };

            vector<ld> rwc(7);
            rwc[1] = 50;
            rwc[2] = 220;
            rwc[3] = -78;
            rwc[4] = 0.5;
            rwc[5] = 10;

            vector<ld> required_angles = change_frame(rwc, link_lengths);

            for(int i=0;i<required_angles.size();i++)    required_angles[i]-=offset_angles[i];

           	for(int i=1;i<=5;i++)	cout<<required_angles[i]<<' ';
}