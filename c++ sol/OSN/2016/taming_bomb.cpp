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
vector<int> a, v;

void f(int x, bool y){
	if(y && v.size() == 2) return;
	cout << (x + 1) << endl;
	cin >> s;
	if(s == "BIP") v.push_back(a.size());
	a.push_back(x);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s >> n >> m >> k;
	
	for(int i = 0; i < 2; i++){
			for(int j = (n + i) / 2 - 1; ~j; j--) f(i * (n / 2) + j, 1);
			for(int j = 0; j < (n + i) / 2; j++) f(i * (n / 2) + j, 1);
	}
	
	while(v.size() < 2) f(0, 1);
	
	int x = min(n - 1, v[0]);
	while(a[v[0] - x] != a[v[1] - x]) x--;
	
	while(v.size() < n) f(a[v[0] - x], 0);

	return 0;
}