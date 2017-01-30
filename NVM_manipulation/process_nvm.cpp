/* Program to extract the camera positions fromthe nvm file */

#include <bits/stdc++.h>
using namespace std;

vector<int> vv[100];	// vector storing camera information related to each click

// each element of the vv contains a vector of size = 10, 
// containing some of the camera co-ordiantes

int get_idx(string s){
	s = s.substr(4);
	int val = 0;
	for(int i = 0; s[i]<='9'&&s[i]>='0';i++){
		val = 10 * val + s[i] - '0';
	}
	cout<<val<<endl;
	return 0;
}

bool usable[101];	// array storing whether the camera positions provide some information or not

int main(){
	freopen("result11.nvm", "r", stdin);
	memset(usable, 0, sizeof usable);

	string s;	cin>>s;	// garbage string for now
	
	int no_of_clicks;	cin>>no_of_clicks;
	cout<<no_of_clicks<<endl;
	string foo = "shot";
	
	int good_poses = 0;

	while(no_of_clicks){
		cin>>foo;	if(foo.substr(0, 4)!="shot")	break;
		int idx = get_idx(foo);
		good_poses++;
		usable[idx] = 1;
		for(int i = 0 ;i <10 ; i++){
			long double x;	cin>>x;
			vv[idx].push_back(x);
		}
	}

	int x[100], y[100], z[100];
	
	for(int i = 0; i< 100; i++)	if(vv[i].size()){
		x[i] = vv[i][5], y[i] = vv[i][6], z[i] = vv[i][7];
	}

	freopen("camera_poses.txt", "w", stdout);
	cout<<good_poses<<endl;
	for(int i = 0; i < 100; i++)	if(usable[i]){
		cout<<i<<' '<<x[i]<<' '<<y[i]<<' '<<z[i]<<endl;
	}
}