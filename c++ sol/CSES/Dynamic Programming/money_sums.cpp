#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'

const int maxv = 100000;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	bool a[maxv + 1];
	memset(a, 0, sizeof(a));
	a[0] = 1;
	
	while(n-- > 0){
		int c;
		cin >> c;
		
		for(int i = maxv; i >= c; i--){
			a[i] |= a[i - c];
		}
	}
	
	vector<int> works;
	
	for(int i = 1; i <= maxv; i++){
		if(a[i]) works.push_back(i);
	}
	
	cout << works.size() << endl;
	
	cout << works[0];
	
	for(int i = 1; i < works.size(); i++) cout << " " << works[i];
	
	cout << endl;

	return 0;
}