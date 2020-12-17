/*
	First ask for the element in the 0th index, and now for value i less than lg(n) ask two set queries: ask for
set of every index such that ith bit is set, and ask for same set + index 0 as well. With this information you can get
the set of pairs between 0 and every index with the ith bit set. Now, hold a value for each value that appears as a
pair between some index and index 0, such that you ad (1 << i) to the value every time the element appears in the set
when querying for the ith bit. Because all values are guaranteed to be distinct, the value for each xor pair will be
equivalent to the index it corresponds to because the sum of powers of two directly map one to one with index numbers
so now you can place each xor pair in there corresponding index and xor it with the value in index 0.
*/

//#include "interactive.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int mxn = 100;
int k;
int a[mxn];
vi v, p, ans;
map<int, int> f;

int ask(int x){
	return a[x - 1];
}

vi get_pairwise_xor(vi v){
	int n = v.size();
	vi ans;
	for(int i : v)
	for(int j : v){
		ans.push_back(a[i - 1] ^ a[j - 1]);
	}
	sort(ans.begin(), ans.end());
	return ans;
}

vi guess(int n){
	k = __lg(n - 1) + 1;
	ans.resize(n);
	ans[0] = ask(1);
	for(int i = 0; i < k; i++){
		v.clear();
		for(int j = 1; j < n; j++) if((j >> i) & 1) v.push_back(j + 1);
		p = get_pairwise_xor(v);
		for(int j : p) if(j) f[j] -= (1 << i);
		v.push_back(1);
		p = get_pairwise_xor(v);
		for(int j : p) if(j) f[j] += (1 << i);
	}
	for(pi i : f) if(i.s) ans[i.s / 2] = i.f ^ ans[0];
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	vi v = guess(n);
	
	for(int i : v) cout << i << " ";
	cout << endl;

	return 0;
}