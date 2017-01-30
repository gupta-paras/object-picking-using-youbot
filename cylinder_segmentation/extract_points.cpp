#include <bits/stdc++.h>
using namespace std;


const long double finf = 1e20;

long double sq(long double x){
	return x*x;
}


int main(){
	
	// parse the contents in the file out.txt

	freopen("out.txt", "r", stdin);
	//freopen("res.txt", "w", stdout);

	long double cylinder_parameters[7];	// array of the cylinder coeficients.
	
	// first three represent ta fixed point on the cylinder axis
	// next three the direction ratios
	// the last one the radius op the cylinder

	
	int sz = 0;
	string garbage;
	
	for(int i=0;i<=20&&cout.eof()==0;i++){
		if(i>=8&&i<=20&&i%2==0){
			long double x;	cin>>x;
			cylinder_parameters[sz++] = x;
		}
		else cin>>garbage;
	}
	for(int i=0;i<7;i++)	cout<<cylinder_parameters[i]<<' ';	cout<<endl;

	long double fixed_points[3];
	long double direction_ratios[3];
	long double radius;

	for(int i=0;i<3;i++)	fixed_points[i] = cylinder_parameters[i];
	for(int i=3;i<6;i++)	direction_ratios[i-3] = cylinder_parameters[i];
	radius = cylinder_parameters[6];

	// parsing done!!
	// use the cylinder parameters to extract information about the cylinder

	// parsing the contents of the file output.ply
	
	//freopen("output.ply", "r", stdin);

	ifstream cylinder_cloud("output.ply");
	garbage = "";
	while(garbage!="end_header"){
		cylinder_cloud>>garbage;
	}	
	cout<<garbage<<endl;
	vector<long double> foo;
	while(cylinder_cloud.eof()==0){
		long double x ;	cylinder_cloud>>x;
		foo.push_back(x);
	}
	int discard = 22;
	while(discard--)	foo.pop_back();

	long double x_mx = -finf, x_mn = finf, y_mx = -finf, 
		y_mn = finf, z_mx = -finf, z_mn = finf;


	if(foo.size()%3)	{
		cout<<"some error has been done in parsing the points!!!";
		return 0;
	}
	for(int i = 0 ; i < foo.size(); i+=3){
		x_mn = min(x_mn, foo[i]);	x_mx = max(x_mx, foo[i]);
		y_mx = max(y_mx, foo[i+1]);	y_mn = min(y_mn, foo[i+1]);
		z_mn = min(z_mn, foo[i+2]);	z_mx = max(z_mx, foo[i+2]);
	}

	cout<<"The ranges of x, y and z respectively are:\n";
	cout<<"Range of x: "<<x_mn<<' '<<x_mx<<endl;
	cout<<"Range of y: "<<y_mn<<' '<<y_mx<<endl;
	cout<<"Range of z: "<<z_mn<<' '<<y_mx<<endl;

	long double x_mid, y_mid, z_mid;
	x_mid = (x_mn + x_mx)/2;
	y_mid = (y_mn + y_mx)/2;
	z_mid = (z_mn + z_mx)/2;

	int mid[] = {x_mid, y_mid, z_mid};

	cout<<"Approximate centre of the cylinder is: "<<x_mid<<' '<<y_mid<<' '<<z_mid<<endl;

	// find the projection of the mid_point on the axis of the cylinder found;

	long double lambda;
	lambda = ( x_mid - fixed_points[0]) * direction_ratios[0]
			 + (y_mid - fixed_points[1]) * direction_ratios[1]
			 + (z_mid - fixed_points[2]) * direction_ratios[2]; 

	cout<<"not normalized lambda: "<<lambda<<endl;
	lambda/= (sq(direction_ratios[0]) + sq(direction_ratios[1]) + sq(direction_ratios[2]));
	cout<<"Normalized lambda: "<<lambda<<endl;

	long double centre[3];

	for(int i = 0; i<3; i++)
		centre[i] = fixed_points[i] + lambda * direction_ratios[i];

	for(int i=0;i<3;i++)	cout<<centre[i]<<' ';

	// the arryay centre contains the calculated centre of the cylinder

	/*
	// create the modified point cloud using the calculated cylinder as the reference

	long double len_line;
	len_line = sqrt(sq(x_mx - x_mn) + sq(y_mx - y_mn) + sq(z_mx - z_mn));

	vector<long double> pc_x, pc_y, pc_z;

	for(int i = -200; i<200; i++)	if(i!=0){
		long double temp = rand();
		temp = abs(temp);
		temp /= temp+1;

		long double x = fixed_points[0] + direction_ratios[0] * len_line*(i*1.0l)/800 + (100- rand()%200)*radius/200.0;
		long double y = fixed_points[1] + direction_ratios[1] * len_line*(i*1.0l)/800+ (100- rand()%200)*radius/200.0;
		long double z = fixed_points[2] + direction_ratios[2] * len_line*(i*1.0l)/800 + (100- rand()%200)*radius/200.0;
		pc_x.push_back(x);	pc_y.push_back(y);	pc_z.push_back(z);
	}

	freopen("epx.txt", "w", stdout);
	cout<<pc_x.size()<<endl;
	for(int i= 0; i<pc_x.size();i ++){
		cout<<pc_x[i]<<' '<<pc_y[i]<<' '<<pc_z[i]<<endl;
	}
	*/

	/*
		The centre of the cylider is stored int the array centre[]
		and the direction ratios of the cylender is storred in the array
		direction_ratios[];
	*/

	freopen("useful_info.txt", "w", stdout);
	cout<<radius<<endl;
	for(int i = 0; i < 3; i++)	cout<<centre [i]<<' ';	cout<<endl;
	for(int i  =0; i< 3; i++)	cout<<direction_ratios[i]<<' ';
}