// In the name of GOD

// program to map camera coordinates to the real world

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

typedef long double ld;

const ld pi = 3.14159;

ld angles[] = {0,0,0,0,0,0};	// read offsets from net
ld delta[] = {.1,.1,.1,.1,.1};
ld abs_angle[] = {0,0,0,0,0,0};
ld l[] = {0,0,0,0,0,0};

void update(){
	abs_angle[2] = angles[2];
	for(int i=3;i<=4;i++)	abs_angle[i] = abs_angle[i-1] + angles[i];	
}

int main(){
	ifstream in("inst.txt");
	ofstream out("angles.txt");
	int idx, val;
	while(!in.eof()){
		in>>idx>>val;
		if(idx<=6){
			angles[idx] += delta[idx] * val;
			update();
		}
		else if (idx==10){
			// print x,y,z in real world values

			ld x,y,z;
			x = 0;
			y = l[2]*cos(abs_angle[2]) + l[3] * cos( abs_angle[3]) + l[4]* cos(abs_angle[4]);
			z = l[2]*sin(abs_angle[2]) + l[3] * sin( abs_angle[3]) + l[4]* sin(abs_angle[4]);

			ld x1,y1,z1;
			x1 = - l[5] * cos(abs_angle[5]);
			y1 = y - l[5] * sin(abs_angle[4]) * sin (abs_angle[5]);
			z1 = z - l[5] * cos(abs_angle[4]) * sin (abs_angle[5]);

			ld x2, y2, z2;
			x2 = y1*sin(abs_angle[1]) + x1 * cos(abs_angle[1]);
			y2 = y1 * cos(abs_angle[1]) - x1 * sin(abs_angle[1]);
			z2 = z1;
			cout<<x2<<' '<<y2<<' '<<z2<<endl;
		}
	}
}