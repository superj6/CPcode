#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 7368788;
int n, m, k;
bool lc[mxn];
vector<int> p;

int f(int x){
	for(int i : p){
		if(x == i % n){
			x = 0;
		}else{
			x -= x > i % n;
			(x += i / n % (n - 1)) %= n - 1;
			x++;
		}
	}
	return ++x;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	k--;
	
	for(int i = 2; p.size() < m; i++) if(!lc[i]){
		p.push_back(i);
		for(int j = 2 * i; j < mxn; j += i) lc[j] = 1;
	} 
	
	for(int i : p){
		if(!k){
			k = i % n;
		}else{
			(k += n - 2 - i / n % (n - 1)) %= n - 1;
			k += k >= i % n;
		}
	}
	
	reverse(p.begin(), p.end());
	
	cout << f((k + 1) % n) << " " << f((n + k - 1) % n) << endl;

	return 0;
}