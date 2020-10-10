/*
  Realize that there is at least starting point such that, if iterating through the array from the starting point and placing the
objects that start at each location in a queue, the queue will always have an object for each location and the queue will be empty
once it reaches the last object before the starting point. If we knew such a location to start on, we could maintain that queue and
place objects on the points with a greedy strategy, putting down the lowest value object if none of them can conquer the current
location, since it will be better to use the higher values later, or otherwise picking the smallest value larger than the current
location, since it's always beneficial conquer an object when possible since no other objects than the ones in the queue will ever
reach the location, and if you were not to use the object now it could at most conquer one object later, which is no better. Now the
only problem is to find a starting location. To do this, pick a random starting location and simulate holding objects in a queue and
placing them down without worrying about the values. While you cannot wrap the objects around, keep moving the starting location 
backwards while maintaining the next positiion possible to place an object, and eventually the objects will be able to wrap around
when you find a valid starting location.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
int n;
int a[mxn], b[mxn], par[mxn];
vector<int> v[mxn];
set<int> s;

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> b[i];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		v[--b[i]].push_back(x);
		par[i] = i;
	}
	
	int st = n - 1;
	for(int i = 0; i < n; st--)
	for(int j = v[st].size(); i < n && j; i++, j--){
		int x = fnd(st);
		j += v[fnd((x + 1) % n)].size();
		par[x] = (x + 1) % n;
	}
	st++;
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		int x = (st + i) % n;
		for(int j : v[x]) s.insert(j);
		if(a[x] < *prev(s.end())){
			s.erase(s.lower_bound(a[x]));
			ret++;
		}else{
			s.erase(s.begin());
		}
	}
	
	cout << ret << endl;
	
	return 0;
}
