#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'

int sig[5] = {1, -1, 1, -1, 1};

struct numset{
	int n = 0;
	int ar[5] = {0, 0, 0, 0, 0};
	
	friend bool operator<(numset a, numset b){
		for(int i = 0; i < 5; i++){
			if(a.ar[i] != b.ar[i]) return a.ar[i] < b.ar[i];
		}
		return false;
	}
};

int nums[5];

numset genset(int x){
	numset ret;
	
	for(int i = 0; i < 5; i++){
		if(x & 1) ret.ar[ret.n++] = nums[i];
		x >>= 1;
	}
	
	return ret;
}

int main(){
	freopen("cowpatibility.in", "r", stdin);
	freopen("cowpatibility.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n;
	cin >> n;
	
	map<numset, long long> amt;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 5; j++) cin >> nums[j];
		sort(nums, nums + 5);
		
		for(int x = 1; x < 32; x++){
			amt[genset(x)]++;
		}
	}
	
	long long res = n * (n - 1) / 2;
	
	for(auto itr : amt){
		res -= (itr.second) * (itr.second - 1) / 2 * sig[itr.first.n - 1];
	}
	
	cout << res << endl;

	return 0;
}