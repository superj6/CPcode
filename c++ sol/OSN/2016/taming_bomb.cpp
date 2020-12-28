#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n, m, k;
string s;
vector<int> v;

void f(int x, int y = 0){
	cout << (x + 1) << endl;
	cin >> s;
	if(s == "BIP") v.push_back(y);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s >> n >> m >> k;
	
	for(int t = 0; t < 2; t++){
		for(int i = 0, x = 0; i < 2; i++){
			for(int j = (n + 1) / 2 - 1; ~j; j--) f(t * (n / 2) + j, x++);
			for(int j = 0; j < (n + 1) / 2 && x < 2 * n; j++) f(t * (n / 2) + j, x++);
		}
		if(!v.empty()){
			int x = t * (n / 2) + (v[1] - v[0] - 1) / 2;
			while(v.size() < n) f(x);
			break;
		}
	}

	return 0;
}