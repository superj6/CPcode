#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main() {
	ifstream fin ("family.in");
	ofstream fout ("family.out");
	
	map<string, int> cow;
	
	vector<int> mother;
	mother.emplace_back(-1);
	mother.emplace_back(-1);
	
	int n, num = 2;
	string a, b;
	int cowa = 0, cowb = 1;
	fin >> n >> a >> b;
	
	cow[a] = cowa;
	cow[b] = cowb;
	
	for(int i = 0; i < n; i++){
		string x, y;
		fin >> x >> y;
		
		if(cow.count(x) == 0){
			cow[x] = num;
			mother.emplace_back(-1);
			num++;
		}
		
		if(cow.count(y) == 0){
			cow[y] = num;
			mother.emplace_back(-1);
			num++;
		}
		
		mother[cow[y]] = cow[x];
	}
	
	int awaya[num], awayb[num];
	for(int i = 0; i < num; i++){
		awaya[i] = -1;
		awayb[i] = -1;
	}
	
	bool found = false;
	int index = cowa, s = -1, t = -1;
	awaya[index] = 0;
	awayb[index] = 0;
	
	while(mother[index] != -1){
		awaya[mother[index]] = awaya[index] + 1;
		index = mother[index];
	}
	
	index = cowb;
	awayb[cowb] = 0;
	if(awaya[index] != -1){
		s = awaya[index];
		t = awayb[index];
		found = true;
	}
	
	while(mother[index] != -1){
		awayb[mother[index]] = awayb[index] + 1;
		index = mother[index];
		
		if(awaya[index] != -1 && !found){
			s = awaya[index];
			t = awayb[index];
			found = true;
		}
	}
	
	/*
	for(int i = 0; i < num; i++){
		cout << mother[i] << " ";
	}
	cout << endl;
	
	for(int i = 0; i < num; i++){
		cout << awaya[i] << " ";
	}
	cout << endl;
	
	for(int i = 0; i < num; i++){
		cout << awayb[i] << " ";
	}
	cout << endl;
	cout << s << " " << t << endl;
	*/
	
	
	
	if(s == -1 && t == -1){
		fout << "NOT RELATED";
	}else if(s == 1 && t == 1){
		fout << "SIBLINGS";
	}else if(t == 0){
		fout << b << " is the ";
		for(int i = 0; i < s - 2; i++){
			fout << "great-";
		}
		if(s > 1) fout << "grand-";
		
		fout << "mother of " << a;
	}else if(s == 0){
		fout << a << " is the ";
		for(int i = 0; i < t - 2; i++){
			fout << "great-";
		}
		if(t > 1) fout << "grand-";
		
		fout << "mother of " << b;
	}else if(t == 1){
		fout << b << " is the ";
		for(int i = 0; i < s - 2; i++){
			fout << "great-";
		}
		fout << "aunt of " << a;
	}else if(s == 1){
		fout << a << " is the ";
		for(int i = 0; i < t - 2; i++){
			fout << "great-";
		}
		fout << "aunt of " << b;
	}else{
		fout << "COUSINS";
	}
	
	return 0;
}