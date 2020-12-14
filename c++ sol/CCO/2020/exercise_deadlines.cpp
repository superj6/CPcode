#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

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
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n;
int a[maxn];
queue<int> q[maxn];
priority_queue<int> pq;
BIT bit;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x = n - x;
		q[x].push(i);
	}
	
	for(int i = 0; i < n; i++){
		while(!q[i].empty()){
			pq.push(q[i].front());
			q[i].pop();
		} 
		if(pq.empty()){
			cout << -1 << endl;
			return 0;
		}
		a[i] = pq.top();
		pq.pop();
	}
	reverse(a, a + n);
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		ret += a[i] - bit.qry(a[i]);
		bit.add(a[i], 1);
	}
	
	cout << ret << endl;
	

	return 0;
}