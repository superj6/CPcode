/*
	Realize that each element has an interval it has to be in the stack, from when it is in the array to the max
index of all elements less than or equal to it. If two intervals intersect, they must be part of different placed
into different groups. If two intervals end at the same index, we can say the one with the rightmost point is the
one that corresponds to an element of a higher value. This means the intervals can be for element i where a[i] is
the index of the ith element in the permutation, l[a[i]] = a[i] * n and r[a[i]] = max(a[j] for j <= i) * n + i. 
	Now to find there intersections, we use the same algorithm as for JOISC Port Facility. You use a dsu to
create bipartite edges between intervals, and hold a stack of pairs of deques, where each deque contains interval
indices sorted by right end points of intervals that are in the same group and the other deque are in the opposite
group. Also higher pairs in the stacks are intervals completely contained within all intervals in lower groups which
means so far no intersections between the groups have taken place. Now you can do some casework to take off
intervals in deques which right end point are less than the current left end point and then test if the current
interval is completely contained within all intervals left in the deques. If not however, while one of the deques
is empty on the top pair of the stack you need to merge the pair with the one below it if the current interval
intersects with intervals in the pair below it. Once your done merging, if the current interval intersects with both
groups, that means the intersecton graph is no longer bipartite, and you output no. Otherwise you place the interval
in the group that it does not intersect, and add an edge between it and an interval in the other group. Now at the
end you can see if the interval must be in a group based on the ones before it, otherwise just put it in group one
and output the group number. It is O(nlgn) since you have to merge deques from small to large.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
#include <deque>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

typedef array<deque<int>, 2> T;

const int mxn = 200001;
ll n;
ll a[mxn], l[mxn], r[mxn], vis[mxn], par[mxn], rnk[mxn];
stack<T> stk;
 
inline ll f(int x){
	return stk.top()[x].empty() ? n * n + 1 : r[stk.top()[x].front()];
}

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

void unf(int x, int y){
	x = fnd(x), y = fnd(y);
	if(x == y) return;
	if(rnk[x] < rnk[y]) swap(x, y);
	rnk[x] += rnk[x] == rnk[y];
	par[y] = x;;
}

void edg(int x, int y){
	unf(x, y + n), unf(x + n, y);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0, x; i < n; i++) cin >> x, a[--x] = i;
	
	for(ll i = 0, j = 0; i < n; i++){
		j = max(j, a[i]);
		l[a[i]] = a[i] * n, r[a[i]] = j * n + i;
		par[i] = i, par[i + n] = i + n;
	}
	
	l[n] = r[n] = n * n;
	for(int i = 0; i <= n; i++){
		while(!stk.empty()){
			for(int j = 0; j < 2; j++){
				while(f(j) < l[i]) stk.top()[j].pop_front();
			}
			if(f(0) > f(1)) swap(stk.top()[0], stk.top()[1]);
			if(!stk.top()[0].empty()) break;
			stk.pop();
		}
		if(stk.empty() || r[i] < f(0)){
			stk.push(T());
			stk.top()[0].push_front(i);
		}else{
			while(stk.size() > 1 && stk.top()[1].empty()){
				T x;
				swap(stk.top(), x);
				stk.pop();
				if(r[i] < f(0)){
					stk.push(T());
					swap(stk.top(), x);
					break;
				}
				edg(i, x[0].front());
				edg(i, stk.top()[0].front());
				if(x[0].size() < stk.top()[0].size()){
					while(!x[0].empty()){
						stk.top()[0].push_front(x[0].back());
						x[0].pop_back();
					}
				}else{
					swap(x[0], stk.top()[0]);
					while(!x[0].empty()){
						stk.top()[0].push_back(x[0].front());
						x[0].pop_front();
					}
				}
			}
			if(r[i] > f(1)){
				cout << "NIE" << endl;
				return 0;
			}
			stk.top()[1].push_front(i);
			edg(i, stk.top()[0].front());
		}
	}
	
	cout << "TAK" << endl;
	
	for(int i = 0; i < n; i++){
		if(vis[fnd(i + n)]) cout << 2;
		else cout << 1, vis[fnd(i)] = 1;
		if(i < n - 1) cout << " ";
	}
	cout << endl;

	return 0;
}