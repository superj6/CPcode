/*
	First for the advisor, you can simulate the process going forward by for every position finding the next
point it is placed in then use a priority queue to take out the highest element when necessary. Now, you only need
n + k bits, k for the starting states and n for each request. The first k bits correspond to the first k objects,
and each of the k + ith bits corresponds to the object in the ith request. When simulating forward, start out with
all bits set to 0, and whenever u do not need to take an object from a request out of the priority queue, you mark
the most recent previous bit position that corresponded to that object with a 1.
	Now for the assistor, whenever you come across a position with bit set to 1, that means that object should
still be in the group next time it is requested, so it cannot be taken out yet. However, if it is set to 0, then
you can add that object to a group to be taken out whenever necessary. Though it will not produce the exact same
outcome as the original simulation, it will not matter which object is taken from the 0 group as it will for sure
be taken sometime before the next request with it anyway, so it will end up needing the same number of PutBack()
operations. You use the first k bits of the string to see if the initial objects should be put in the 0 group, then
the requests will each correspond to the next n bits. 
*/

//#include "advisor.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200000;
int b[mxn], f[mxn], p[mxn], ans[mxn];
priority_queue<pi> pq;

void WriteAdvice(int x){ cout << x << " ";}

void ComputeAdvice(int *a, int n, int k, int m){
	memset(b, -1, sizeof(b));
	memset(p, 0x3f, sizeof(p));
	for(int i = n - 1; ~i; i--) f[i] = p[a[i]], p[a[i]] = i;
	for(int i = 0; i < k; i++) pq.push({p[i], b[i] = i});
	for(int i = 0; i < n; i++){
		if(~b[a[i]]) ans[b[a[i]]] = 1;
		else b[pq.top().s] = -1, pq.pop();
		b[a[i]] = i + k, pq.push({f[i], a[i]});
	}
	for(int i = 0; i < n + k; i++) WriteAdvice(ans[i]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> k >> m;
	
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	ComputeAdvice(a, n, k, m);
	
	cout << endl;
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////


//#include "assistant.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int f[mxn];
stack<int> v;

int GetRequest(){
	int x;
	cin >> x;
	return x;
}

void PutBack(int x){ cout << x << " ";}

void Assist(unsigned char *a, int n, int k, int m){
	for(int i = 0; i < k; i++){
		f[i] = 1;
		if(!a[i]) v.push(i);
	} 
	for(int i = 0; i < n; i++){
		int x = GetRequest();
		if(!f[x]) f[v.top()] = 0, PutBack(v.top()), v.pop();
		if(!a[k + i]) v.push(x);
		f[x] = 1;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	int n, m, k;
	cin >> n >> k >> m;
 
	unsigned char a[m];
	for(int i = 0, x; i < m; i++) cin >> x, a[i] = x;
 
	Assist(a, n, k, m);
	
	cout << endl;
 
	return 0;
}
