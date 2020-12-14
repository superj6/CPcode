#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200001;

struct BIT{
	int bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
 
	int qry(int x){
		int ret = 0;
		for(x++; x > 0; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n;
int a[maxn], b[maxn];

long long solve1(){
	BIT bit;
	long long ret = 0;
	for(int i = 0; i < n; i++){
		ret += b[i] - bit.qry(b[i]);
		bit.add(b[i], 1);
	}
	return ret;
}

int solve2(){
	int aa[maxn], bb[maxn];
	memcpy(aa, a, sizeof(a));
	memcpy(bb, b, sizeof(b));
	int ret = 0;
	for(int i = 0; i < n; i++){
		if(bb[i] != i){
			ret++;
			swap(aa[bb[i]], aa[i]);
			swap(bb[i], bb[aa[bb[i]]]);
		}
	}
	return ret;
}

int solve3(){
	vector<int> v;
	int ret = 0;
	for(int i = 0; i < n; i++){
		int x = upper_bound(v.begin(), v.end(), a[i]) - v.begin();
		if(x == v.size()) v.push_back(a[i]);
		else v[x] = a[i];
		ret = max(ret, x + 1);
	}
	return n - ret;
}

int solve4(){
	int ret = 1;
	for(int i = n - 2; i >= 0 && b[i] < b[i + 1]; i--, ret++);
	return n - ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		b[a[i]] = i;
	} 
	
	cout << solve1() << " " <<  solve2() << " " << solve3() << " " << solve4() << endl;

	return 0;
}