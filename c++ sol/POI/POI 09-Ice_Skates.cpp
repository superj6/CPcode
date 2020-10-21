/*
  We can use hall's theorem with a segment tree. Think about the problem as a bipartite graph, where a node's on the left side are
the people and nodes on the right side are the shoes of each size. Each node on the left size then has a set of edges covering the
consecutive range of right nodes on the right side that correspond to the range of shoe sizes that it can go to. Now we need a perfect
matching for the problem to be satisfied, and hall's theorem says a perfect matching exists if every subset of nodes on the left side
is connected to at least as many distinct nodes on the right side as there are nodes in the left subset. 
  Now to use properties of the problem, since each left node is only connected to a consecutive range, we would only have to check
consecutive ranges of right nodes to see if they satisfy hall's, and because each left node covers a range of equal length, that means
each consecutive range of left nodes corresponds to a consecutive range of right nodes with the endpoints of the left ranges mapping to
the endpoints of the right range. This hints that we can use a segment tree to find the worst range using range sums and see if the
problem is still satisfied after each update.
  To use a segment tree, we will imagine we are holding prefix sums inside, and the count of shoes in a range will be negative while
count of people will be positive. Now, the condition of each range of people's corresponding shoe range having more shoes than people 
is equivalant to the sum of people minus shoes in the corresponding ranges being less than or equal to 0. This mean the worst range will
be the range with the maximum sum of people minus shoes. To find this value as we merge in the segment tree, we can hold the largest 
prefix sum and smallest prefix sum, and then the maximum sum in a range will be its left value, its right value, or the right max prefix
minus the left min prefix. Now it is obvious how the queries will be handled, we can just update how many people are in the range
corresponding to their shoe sizes range, and maintain an implicit prefix sum of people as nodes are merged and see if the worst range is
less than or equal to 0. This will solve the problem in O(qlgn).
  Realize this idea can be further extended, where each shoe type has a different amount of shoes, and each person can go to a different
sized range as long as no range is within another range, as if one is within another we won't have the condition of a endpoints of 
consecutive people corresponding to endpoints of consecutive shoes. We would then just have to handle the amount of shoes in a range to
subtract in the sum more carefully, and you could even have updates to amounts of shoes if you do lazy updates on the segment tree that
correspond to the range of people who have that shoe within their range. A more complicated problem that uses some of this generalization
plus another seperate insight is https://codeforces.com/gym/102268/problem/D.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

struct T{
	ll s, mn, mx, v;
	
	T friend operator+(T l, T r){
		return {
			l.s + r.s,
			min(l.mn, l.s + r.mn),
			max(l.mx, l.s + r.mx),
			max({l.v, r.v, l.s + r.mx - l.mn})
		};
	}
};

const int mxn = 1 << 18;
int n, m, k, w, q;
T t[mxn << 1];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q >> k >> m;
	w = 1 << (__lg(n - 1) + 1);
	
	for(int i = 0; i < w; i++){
		t[w + i].s = 0;
		t[w + i].mn = (ll)-k * min(n, i);
		t[w + i].mx = (ll)-k * min(n, i + m + 1);
		t[w + i].v = t[w + i].mx - t[w + i].mn;
	}
	
	for(int i = w - 1; i; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	
	while(q--){
		int x, y;
		cin >> x >> y;
		x--;
		t[w + x].s += y, t[w + x].mx += y, t[w + x].v += y;
		for(int i = (w + x) >> 1; i; i >>= 1) t[i] = t[i << 1] + t[i << 1 | 1];
		cout << (t[1].v <= 0 ? "TAK" : "NIE") << endl;
	}

	return 0;
}
